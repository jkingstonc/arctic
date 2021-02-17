;;kernel.asm


%define MEMORY_MAP 0x1
%define PAGE_ALIGN 0x2
%define VBE_ENABLE 0x4

;nasm directive - 32 bit
bits 32


  
section .multiboot
  ;multiboot1
  align 4
  dd 0x1BADB002                         ;magic
  dd MEMORY_MAP|PAGE_ALIGN|VBE_ENABLE                  ;flags  (bit 1 set for memory map, bit 0 set for page aligning)
  dd - (0x1BADB002 + (MEMORY_MAP|PAGE_ALIGN|VBE_ENABLE)) ;checksum. m+f+c should be zero
addrinfo_ignored:
  dd 0
  dd 0
  dd 0
  dd 0
  dd 0
videomode:
  dd 0
  dd 1280 ; VBE width
  dd 720 ; VBE height
  dd 32   ; VBE pixel depth

  ; ; multiboot2 (qemu doesn't support yet!)
  ; header_start:
  ; dd 0xe85250d6                ; magic number
  ; dd 0                         ; protected mode code
  ; dd header_end - header_start ; header length
  ; dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; checksum
  ; ; required end tag
  ; dw 0    ; type
  ; dw 0    ; flags
  ; dd 8    ; size
  ; header_end:


section .text
global start
extern main	        ;kmain is defined in the c file

start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  sub esp, 8 ; so we can align the arguments
  push eax  ; push magic number
  push ebx  ; push multiboot info
  call main
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
global stack_space
stack_space:
