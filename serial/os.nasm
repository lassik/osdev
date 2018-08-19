bits   32
extern main
global start
global cpu_in8
global cpu_out8

section .multiboot

align 8

header:
	dd    0xe85250d6
	dd    0
	dd    header_end - header
	dd    0x100000000 - (0xe85250d6 + 0 + (header_end - header))
	align 8

header_tag_end:
	dd 0
	dd 8

header_end:

	section .text

start:
	mov  esp, stack_end
	call main

.spin:
	hlt
	jmp .spin

cpu_in8:
	mov   edx, [esp+4]
	in    al, dx
	movzx eax, al
	ret

cpu_out8:
	mov eax, [esp+8]
	mov edx, [esp+4]
	out dx, al
	ret

section .bss

stack:
	resb 4096

stack_end:
