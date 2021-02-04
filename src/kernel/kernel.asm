;;kernel.asm


;nasm directive - 32 bit
bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00000001|0x00000002                  ;flags  (bit 1 set for memory map, bit 0 set for page aligning)
        dd - (0x1BADB002 + (0x00000001|0x00000002)) ;checksum. m+f+c should be zero

global start
extern main	        ;kmain is defined in the c file

start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  call main
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
global stack_space
stack_space:
