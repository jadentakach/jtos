bits 32
extern main
global _start

_start:
	cli

	mov esp, 0x90000
	mov ebp, esp

	call main

.halt:
	cli
	hlt
	jmp .halt
