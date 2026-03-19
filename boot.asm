MAGIC    equ 0x1BADB002
FLAGS    equ 0x0
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    call kernel_main
    hlt

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
