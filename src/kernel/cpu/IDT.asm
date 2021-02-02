section .text


%macro exec_isr 1
global exec_%1_isr
extern exec_%1
exec_%1_isr:
   cli
   pushad  
   call exec_%1
   popad                   
   sti
   iret           
%endmacro

exec_isr 0
exec_isr 1
exec_isr 2
exec_isr 3
exec_isr 4
exec_isr 5
exec_isr 6
exec_isr 7
exec_isr 8
exec_isr 9
exec_isr 10
exec_isr 11
exec_isr 12
exec_isr 13
exec_isr 14
exec_isr 15
exec_isr 16
exec_isr 17
exec_isr 18
exec_isr 19

global exec_20_isr
extern timer_isr
exec_20_isr:
   cli
   pushad  
   call timer_isr
   popad                   
   sti
   iret

global exec_keyboard_isr
extern keyboard_isr
exec_keyboard_isr:
   cli
   pushad  
   call keyboard_isr
   popad                   
   sti
   iret