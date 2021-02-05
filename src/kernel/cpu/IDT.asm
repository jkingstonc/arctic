section .text


%macro interrupt_isr 1
global interrupt_isr_%1
extern interrupt_handler
interrupt_isr_%1:
   cli           ; clear interrupts
   push byte 0
   push byte %1
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
   push eax
   call interrupt_handler
   pop eax
   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP          
%endmacro

interrupt_isr 0
interrupt_isr 1
interrupt_isr 2
interrupt_isr 3
interrupt_isr 4
interrupt_isr 5
interrupt_isr 6
interrupt_isr 7
interrupt_isr 8
interrupt_isr 9
interrupt_isr 10
interrupt_isr 11
interrupt_isr 12
interrupt_isr 13
interrupt_isr 14
interrupt_isr 15
interrupt_isr 16
interrupt_isr 17
interrupt_isr 18
interrupt_isr 19
interrupt_isr 20
interrupt_isr 21
interrupt_isr 22
interrupt_isr 23
interrupt_isr 24
interrupt_isr 25
interrupt_isr 26
interrupt_isr 27
interrupt_isr 28
interrupt_isr 29
interrupt_isr 30
interrupt_isr 31
interrupt_isr 32
interrupt_isr 33
interrupt_isr 34
interrupt_isr 35
interrupt_isr 36
interrupt_isr 37
interrupt_isr 38
interrupt_isr 39
interrupt_isr 40
interrupt_isr 41
interrupt_isr 42
interrupt_isr 43
interrupt_isr 44