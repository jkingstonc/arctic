
section .text



global set_idt

set_idt:
    mov edx, [esp+4] ; get the ptr of the idt from the first argument
    lidt [edx]
    sti         ; enable interrupts
    ret 



extern keyboard_interrupt_handler
keyboard_interrupt: ; the isr for the keyboard
    cli
    pusha
    call keyboard_interrupt_handler
    popa
    sti
    iret
    global keyboard_interrupt