section .text

global set_gdt

set_gdt:
    cli
    call enable_a20
    mov eax, [esp+4]
    lgdt [eax]
    jmp enter_protected
    jmp reload_registers
    jmp 0x08:done ; long jump to flush the CPU
done:
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
    test al, 2
    jnz after
    or al, 2
    and al, 0xFE
    out 0x92, al
    after:
    ret

reload_registers:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret