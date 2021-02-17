ENTRY(start)

SECTIONS
 {
   . = 0x100000;
   .boot : {
        *(.multiboot) /*places multiboot_header at the beginning*/
   }
   .text BLOCK(4K) : ALIGN(4K) { 
     *(.text) 
     }
   .data BLOCK(4K) : ALIGN(4K) { *(.data) }
   .bss  BLOCK(4K) : ALIGN(4K) { *(.bss)  }
   end_of_kernel = .; _end_of_kernel = .; __end_of_kernel = .;
 }