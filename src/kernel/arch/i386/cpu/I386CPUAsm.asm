section .text



global setup_fpu
setup_fpu:
    ; this assumes we have an fpu...
    ;mov eax, cr4
    ;or eax, 0x200
    ;mov cr4, eax


    ; finally set the control word
    ; fldcw 0x37f   ; writes 0x37f into the control word: the value written by F(N)INIT
    ; fldcw 0x37e   ; writes 0x37e, the default with invalid operand exceptions enabled
    ; fldcw 0x37a   ; writes 0x37a, both division by zero and invalid operands cause exceptions.
    
    finit

    ret


global enable_sse
enable_sse:
    ; this assumes we have sse support...
    mov eax, cr0        ; move cr0 into eax
    and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
    or ax, 0x2			;set coprocessor monitoring  CR0.MP
    mov cr0, eax
    mov eax, cr4
    or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, eax
    ret



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