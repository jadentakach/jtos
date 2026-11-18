bits 32
extern main
global _start

_start:
	mov esp, 0x90000
	and esp, 0xFFFFFFF0

	call main
	jmp $

.hang:
	jmp .hang
