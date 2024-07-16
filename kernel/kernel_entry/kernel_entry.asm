[bits 32]
[extern main]   ; Defines calling point. Needs to have same as the kernel.c 'main' function

call main
jmp $