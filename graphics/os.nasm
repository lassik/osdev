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

header_tag_framebuffer:
	dd 5
	dd header_tag_framebuffer_end - header_tag_framebuffer
	dd 800
	dd 600
	dd 32

header_tag_framebuffer_end:
	align 8

header_tag_end:
	dd 0
	dd 8

header_end:

	section .text

start:
	mov  esp, stack_end
	push ebx
	push eax
	call main

.spin:
	hlt
	jmp .spin

section .bss

stack:
	resb 4096

stack_end:
