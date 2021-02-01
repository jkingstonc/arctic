gdtr DW 0 ; for limit storage
     DD 0 ; for base storage

section .text

global set_gdt

set_gdt:
    call enable_a20
    cli
    mov eax, [esp+4]
    mov [gdtr+2], eax
    mov ax, [esp+8]
    mov [gdtr], ax
    lgdt [gdtr]
    jmp enter_protected
    jmp 08h:reload_registers ; 08h points to the first descriptor in the GDT which is the PM code segment
    ret

; set the cr0 register to 1 to signal we are in 32-bit protected mode
enter_protected:
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    ret

; this allows us to use more than 20 lines of memory
enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

reload_registers:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret