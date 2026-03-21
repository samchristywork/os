MAGIC    equ 0x1BADB002
FLAGS    equ 0x4          ; bit 2: request linear framebuffer
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0, 0, 0, 0, 0     ; address fields (unused, bit 16 not set)
    dd 0                  ; mode_type: 0 = linear graphics
    dd 800                ; width
    dd 600                ; height
    dd 32                 ; depth (bpp)

section .text
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    push ebx             ; multiboot info pointer → kernel_main arg
    call kernel_main
    hlt

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
