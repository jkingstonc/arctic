
section .text
; read the amount of memory
global detect_memory
detect_memory:


    ; move the pointer to the memory map into eax
    push ebp
    mov ebp, esp
   ; mov eax, [esp+8]

    mov ax, 0
    mov es, ax
    mov di, [esp+8] ; store the memory map in di
    mov edx, 0x534D4150 ; SMAP in ASCII
    xor ebx, ebx

    .repeat:
        mov eax, 0xE820
        mov ecx, 24      ; each entry is 24 bytes
        int 0x15         ; call the bios to get the memory listing
        cmp ebx, 0       ; check if the bios is done
        je .finished
        add di, 24
        inc byte [esp+8] ; move into the next table entry
        jmp .repeat
    .finished:

    ; clean up the stack
    mov esp, ebp       
    pop ebp

    ret