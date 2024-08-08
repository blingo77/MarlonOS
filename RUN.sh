#!/usr/bin/bash

# creates the bootsector and moves into main directory
cd boot/main
make bootsector.bin
mv bootsector.bin ../..
cd ../..

nasm kernel/kernel_entry/kernel_entry.asm -f elf -o kernel_entry.o

/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

nasm cpu/interrupt.asm -f elf -o cpu/interrupt.o

/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c libc/mem.c -o libc/mem.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c libc/string.c -o libc/string.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c drivers/port.c -o drivers/port.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c drivers/screen.c -o drivers/screen.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c drivers/keyboard.c -o drivers/keyboard.o


/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c cpu/idt.c -o cpu/idt.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c cpu/isr.c -o cpu/isr.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c cpu/timer.c -o cpu/timer.o

i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel/kernel.o cpu/interrupt.o drivers/port.o drivers/screen.o cpu/idt.o cpu/isr.o cpu/timer.o  drivers/keyboard.o libc/mem.o libc/string.o --oformat binary --allow-multiple-definition

cat bootsector.bin kernel.bin > os-image.bin
