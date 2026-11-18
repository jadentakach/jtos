org 0x7C00
bits 16

KERNEL_OFFSET equ 0x1000

start:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov bp, 0x9000
	mov sp, bp

	mov [boot], dl

	in al, 0x92
	or al, 2
	out 0x92, al

	mov bx, KERNEL_OFFSET
	mov ah, 0x02
	mov al, 1
	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02
	mov dl, [boot]
	int 0x13
	jc disk_error

	xor ah, ah
	mov al, 0x13
	int 0x10

	cli
	lgdt [gdt_desc]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp CODE_SEG:init_pm

disk_error:
	mov si, DISK_ERR_MSG

.print_loop:
	lodsb
	or al, al
	jz .hang
	mov ah, 0x0E
	int 0x10
	jmp .print_loop

.hang:
	jmp $

gdt_start:
	dq 0x0

gdt_code:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00

gdt_data:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

gdt_end:

gdt_desc:
	dw gdt_end - gdt_start - 1
	dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32

init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	mov eax, KERNEL_OFFSET
	call eax
	jmp $

boot db 0
DISK_ERR_MSG db 'disk read error', 0

times 510-($-$$) db 0
dw 0xAA55
