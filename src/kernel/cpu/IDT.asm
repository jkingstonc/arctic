section .text

global set_idt

set_idt:
    mov edx, [esp+4] ; get the ptr of the idt from the first argument
    lidt [edx]

    sti         ; enable interrupts
    ret 



extern irq_handler
global irq_handler
global irq
irq:
  pusha
  call irq_handler
  popa
  iret


extern irq1_handler
global irq1_handler
global irq1
irq1:
  pusha
  call irq1_handler
  popa
  iret



extern kprint_test