

section .text
[bits 32]
global enable_paging
enable_paging:
    ; assume we have been passed the page directory
    ; move the page directory into cr3
    push ebp
    mov ebp, esp

    mov eax, [esp+8]

    mov cr3, eax

    mov esp, ebp       
    pop ebp

    ; set paging and protection bits in cr0
    mov eax, cr0
    or eax, 0x80000011
    mov cr0, eax
    
    ; enable 4MiB pages
    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax

    ret