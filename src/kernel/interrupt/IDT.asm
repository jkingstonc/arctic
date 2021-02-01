idrt DW 0 ; for length
     DD 0 ; for base pointer storage

section .text

global set_idt

set_idt:
    mov eax, [esp+4]
    mov [idrt+2], eax
    mov ax, [esp+8]
    mov [idrt], ax
    lidt [idrt]
    sti         ; enable interrupts
    ret 


extern keyboard_interrupt_handler
global keyboard_interrupt
keyboard_interrupt: ; the isr for the keyboard
    pusha
    call keyboard_interrupt_handler
    popa
    iretd ; interrupt return quad