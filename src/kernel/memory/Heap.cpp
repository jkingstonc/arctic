#include <kernel/memory/Heap.h>
#include <kernel/Kernel.h>
#include <kernel/io/Debug.h>
#include <kernel/Panic.h>
#include <util/Mem.h>

namespace Memory{


    u1 operator<(HeapEntryBoundary& first, HeapEntryBoundary& second){
        IO::dbg() << "TEST comparing heap entry boundaries\n";
        return first.size < second.size;
    }

    Heap::Heap(){
    }

    void Heap::setup(u32 start_addr, u32 size){
        // check if the start address is page aligned (4kb) and if not align it
        if(start_addr&0x00000FFF!=0){
            start_addr &= 0xFFFFF000;
            start_addr += 0x1000;
        }
        m_allocation_map = OrderedVector<u32>(); // @TODO this may need to be moved into a specific location
        m_allocation_map.set_comparitor([](void* first, void* second){
            HeapEntryBoundary* boundary_one = (HeapEntryBoundary*)first;
            HeapEntryBoundary* boundary_two = (HeapEntryBoundary*)second;
            return boundary_one->size<boundary_two->size;
        });
        m_readonly=0;
        m_supervisor_mode=0;
        m_start_addr=start_addr+sizeof(u32)*HEAP_MAX_ENTRY;
        m_end_addr=m_start_addr+size;
        m_max_arrd=m_end_addr;

        // create one huge hole
        HeapEntryBoundary* first_header = (HeapEntryBoundary*)m_start_addr;
        memset(first_header, 0, sizeof(HeapEntryBoundary));
        first_header->magic=HEAP_ENTRY_MAGIC;
        first_header->hole=HEAP_ENTRY_HOLE;
        first_header->mode=HEAP_ENTRY_HEADER;
        first_header->size=size-sizeof(HeapEntryBoundary)*2; // we subtract the sizeof a boundary for the header & footer
        
        HeapEntryBoundary* first_footer = (HeapEntryBoundary*)(m_end_addr-sizeof(HeapEntryBoundary));
        memset(first_footer, 0, sizeof(HeapEntryBoundary));
        first_footer->magic=HEAP_ENTRY_MAGIC;
        first_footer->hole=HEAP_ENTRY_HOLE;
        first_footer->mode=HEAP_ENTRY_FOOTER;
        first_footer->size=size-sizeof(HeapEntryBoundary)*2; // we subtract the sizeof a boundary for the header & footer

        // add the large hole into the allocation map
        m_allocation_map.put((u32)first_header);
        IO::dbg() << "heap created at addr="<<(s32)m_start_addr<<" with size="<<(s32)size<<"\n";
        ASSERT(first_header->magic==HEAP_ENTRY_MAGIC, "WTF magic not being set!\n");
    }

    Heap::~Heap(){}

    u32 Heap::alloc(u32 size, u1 page_align){
        // find the smallest hole that we can allocate given the total size which is a header + footer
        u32 total_size = sizeof(HeapEntryBoundary)*2 + size;

        s32 hole = find_smallest_hole(total_size, page_align);
        if(hole==-1){
            PANIC("kernel heap allocation failed, not enough memory\n");
            return 0;
        }
        // set the header to used and insert the footer
        HeapEntryBoundary* heap_header = (HeapEntryBoundary*)m_allocation_map[hole];
        HeapEntryBoundary* heap_footer = (HeapEntryBoundary*)(((u32)heap_header)+sizeof(HeapEntryBoundary)+heap_header->size);

        u32 heap_header_addr = (u32)heap_header;                             
        u32 allocation_addr = heap_header_addr+sizeof(HeapEntryBoundary);
        u32 found_size=heap_header->size;

        heap_header->hole=HEAP_ENTRY_FULL;
        heap_header->size=size;

        // if the hole isn't page aligned, then 
        if(page_align && heap_header_addr&0xfffff000){

            u32 new_header_addr = ((u32)heap_header_addr&0xfffff000)+0x1000;
            u32 address_diff = new_header_addr-heap_header_addr;
            // the shrinked size = address difference - the header and the new footer
            u32 shrinked_size = address_diff-(sizeof(HeapEntryBoundary)*1);
            #ifdef DEBUG_HEAP
                IO::dbg() << "new addr="<<new_header_addr<<", old="<<heap_header_addr<<"\n";
                IO::dbg() << "original size="<<found_size<<", shrinked size="<<shrinked_size<<"\n";
                IO::dbg() << "diff="<<address_diff<<"\n";
            #endif


            HeapEntryBoundary* new_header = (HeapEntryBoundary*)new_header_addr;
            new_header->magic=HEAP_ENTRY_MAGIC;    
            new_header->mode=HEAP_ENTRY_HEADER;    
            new_header->hole=HEAP_ENTRY_FULL;
            new_header->size = size;  

            // now create the footer to go to the left of this new aligned header
            HeapEntryBoundary* footer = (HeapEntryBoundary*)(new_header_addr-sizeof(HeapEntryBoundary));
            footer->magic = HEAP_ENTRY_MAGIC;
            footer->mode = HEAP_ENTRY_FOOTER;  
            footer->hole = HEAP_ENTRY_HOLE;
            footer->size = shrinked_size;

            // update the old header
            heap_header->hole = HEAP_ENTRY_HOLE;
            heap_header->size = shrinked_size;

            heap_header=new_header;
            heap_header_addr=new_header_addr;
            allocation_addr=new_header_addr+sizeof(HeapEntryBoundary);

            found_size-= address_diff;

            // after page aligning we have this
            //                 \/ page boundary
            // |header   footer|header    footer|header    footer|
        }

        // after not page aligning we have this
        // |header   footer|header    footer|

        // create the footer to insert into the middle of the found block to indicate this is now being used
        HeapEntryBoundary* tmp_footer = (HeapEntryBoundary*)((u32)heap_header+sizeof(HeapEntryBoundary)+size);
        memset(tmp_footer, 0, sizeof(HeapEntryBoundary));
        tmp_footer->magic=HEAP_ENTRY_MAGIC;
        tmp_footer->mode=HEAP_ENTRY_FOOTER;
        tmp_footer->hole=HEAP_ENTRY_FULL;
        tmp_footer->size=size;

        // now create the new header after the footer
        HeapEntryBoundary* tmp_header = (HeapEntryBoundary*)((u32)tmp_footer+sizeof(HeapEntryBoundary));
        memset(tmp_header, 0, sizeof(HeapEntryBoundary));
        tmp_header->magic=HEAP_ENTRY_MAGIC;
        tmp_header->mode=HEAP_ENTRY_HEADER;
        tmp_header->hole=HEAP_ENTRY_HOLE;

        // @TODO this is the wrong size
        tmp_header->size= found_size - size - sizeof(HeapEntryBoundary)*2; // this is broken when page aligning

        // now we finally update the size of the footer that is the original footer
        ASSERT(heap_footer->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
        ASSERT(heap_footer->mode==HEAP_ENTRY_FOOTER, "heap entry isn't footer\n");



        heap_footer->size=tmp_header->size;


        // insert the header into the allocation map
        m_allocation_map.put((u32)tmp_header);

        // remove the heap header from the allocation map as it's now being used
        // we have to find the idx again as it will be shifted around after adding new headers
        s32 header_idx = m_allocation_map.find((u32)heap_header);
        // this takes into account if we have just shifted the header via a page align
        if(header_idx!=-1){
            m_allocation_map.remove(header_idx);
        }
        return allocation_addr;
    }

    u32 Heap::realloc(u32 ptr, u1 page_align){
        return ptr;
    }

    void Heap::free(u32 addr){
        if(addr==0) return;
        HeapEntryBoundary* heap_entry_header = (HeapEntryBoundary*)(addr-sizeof(HeapEntryBoundary));
        HeapEntryBoundary* heap_entry_footer = (HeapEntryBoundary*)(addr+heap_entry_header->size);

        ASSERT(heap_entry_header->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
        ASSERT(heap_entry_header->mode==HEAP_ENTRY_HEADER, "heap entry isn't header\n");
        ASSERT(heap_entry_footer->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
        ASSERT(heap_entry_footer->mode==HEAP_ENTRY_FOOTER, "heap entry isn't footer\n");

        heap_entry_header->hole=HEAP_ENTRY_HOLE;
        heap_entry_footer->hole=HEAP_ENTRY_HOLE;

        //      this is us, we need to merge with either side
        //              \/
        // footer|header   footer|header
        

        // when we first merge with the left, we update the value of heap_entry_header to the left hole
        // so when we then merge with the right we have already merged with the left


        // check if there is a hole to the left aswel, if so, we can merge with it
        HeapEntryBoundary* test_footer = (HeapEntryBoundary*)(((u32)heap_entry_header)-sizeof(HeapEntryBoundary));
        if(test_footer->magic==HEAP_ENTRY_MAGIC 
        && test_footer->mode==HEAP_ENTRY_FOOTER
        && test_footer->hole==HEAP_ENTRY_HOLE){
            IO::dbg() << "merging with left\n";
            // adjust the size of the footer
            HeapEntryBoundary* test_header = (HeapEntryBoundary*)((u32)test_footer-(sizeof(HeapEntryBoundary)*2)-test_footer->size);
            ASSERT(test_header->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
            ASSERT(test_header->mode==HEAP_ENTRY_HEADER, "heap entry isn't header\n");
            test_header->size = test_header->size + heap_entry_header->size + sizeof(HeapEntryBoundary)*2;
            // update the size of our footer now
            heap_entry_footer->size=test_header->size;
            // we dont have to touch the header, we can just remove it and update the actual header now
            m_allocation_map.remove((u32)heap_entry_header);
            heap_entry_header = test_header;
        }

        HeapEntryBoundary* test_header = (HeapEntryBoundary*)((u32)heap_entry_footer+sizeof(HeapEntryBoundary));
        if(test_header->magic==HEAP_ENTRY_MAGIC 
        && test_header->mode==HEAP_ENTRY_HEADER
        && test_header->hole==HEAP_ENTRY_HOLE){
            IO::dbg() << "merging with right\n";
            // adjust the size of the current header
            // its new size is incremented by the size of the right hole + header*2 (to merge with our footer and the tmp header)
            u32 original_header_size = heap_entry_header->size;
            heap_entry_header->size = heap_entry_header->size + test_header->size + sizeof(HeapEntryBoundary)*2;
            // adjust the size of the footer
            HeapEntryBoundary* test_footer = (HeapEntryBoundary*)((u32)test_header+sizeof(HeapEntryBoundary)+test_header->size);
            ASSERT(test_footer->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
            ASSERT(test_footer->mode==HEAP_ENTRY_FOOTER, "heap entry isn't footer\n");
            test_footer->size = test_footer->size + original_header_size + sizeof(HeapEntryBoundary)*2;
            // we dont have to touch the header, we can just remove it
            m_allocation_map.remove((u32)test_header);
        }
        ASSERT(heap_entry_header->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
        ASSERT(heap_entry_header->mode==HEAP_ENTRY_HEADER, "heap entry isn't header\n");
        // finally add the header back into the allocation map
        m_allocation_map.put((u32)heap_entry_header);
    }

    
    // find the smallest hole inside the allocation map
    s32 Heap::find_smallest_hole(u32 size, u1 page_align){
        s32 i=0;
        while(i<m_allocation_map.size()){
            HeapEntryBoundary* heap_entry = (HeapEntryBoundary*)m_allocation_map[i];
            ASSERT(heap_entry->magic==HEAP_ENTRY_MAGIC, "heap entry magic invalid\n");
            ASSERT(heap_entry->mode==HEAP_ENTRY_HEADER, "heap entry isn't header\n");
            if(page_align){
                // see if we can fit a page inside this heap_entry size
                
                u32 header_location = (u32)heap_entry;
                s32 aligned_offset=0;
                // if the entry data is not page aligned then align it
                if(header_location+sizeof(HeapEntryBoundary) & 0xFFFFF000){
                    // get the offset from the header that alignes with a page
                    aligned_offset = 0x1000 - (header_location+sizeof(HeapEntryBoundary))%0x1000;
                }
                s32 aligned_hole_size = (s32)heap_entry->size - aligned_offset;
                // we can fit the size into the page aligned header
                if(aligned_hole_size >= size)
                    break;
            }else if(heap_entry->size >= size){
                // we have found a an entry that is suitable
                break;
            }
            i++;
        }
        // return -1 if we havet found a hole
        if(i==m_allocation_map.size())
            return -1;
        return i;
    }


    void Heap::debug(){
        for(int i=0;i<m_allocation_map.size();i++){
            auto hole = (HeapEntryBoundary*)m_allocation_map[i];
            auto test_footer = (HeapEntryBoundary*)(m_allocation_map[i]+sizeof(HeapEntryBoundary)+hole->size);
            if(test_footer->magic!=HEAP_ENTRY_MAGIC){
                IO::dbg() << "HEAP DEBUG: (HOLE HAS NO FOOTER) hole addr="<<m_allocation_map[i]<<", hole size="<<hole->size<<"\n";
            }else{
                IO::dbg() << "HEAP DEBUG:                      hole addr="<<m_allocation_map[i]<<", hole size="<<hole->size<<"\n";
            }

        }
    }
}