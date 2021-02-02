section .text


global enter_protected
enter_protected:
    call setup_a20
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp 0x8:update_registers


; this allows us to use more than 20 lines of memory
setup_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; set the data segment registers to the GDT data segment
update_registers:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ret