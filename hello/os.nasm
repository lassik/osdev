bits   32
global start

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
	mov esi, hello
	mov edi, 0xb8000
	mov ah, 0x0f
	cld
	lodsb

.char:
	stosw
	lodsb
	test al, al
	jnz  .char

.spin:
	hlt
	jmp .spin

hello:
	db 'This is easier than coloring between the lines!', 0
