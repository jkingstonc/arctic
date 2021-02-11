; section .text


; global set_gdt
; set_gdt:
;     cli
;     mov eax, [esp+4]
;     lgdt [eax]
;     ret