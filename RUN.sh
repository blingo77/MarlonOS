#!/usr/bin/bash

# creates the bootsector and moves into main directory
cd boot/main
make bootsector.bin
mv bootsector.bin ../..
cd ../..

nasm kernel/kernel_entry/kernel_entry.asm -f elf -o kernel_entry.o

/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

nasm cpu/interrupt.asm -f elf -o cpu/interrupt.o

/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c kernel/util.c -o kernel/util.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c drivers/port.c -o drivers/port.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c drivers/screen.c -o drivers/screen.o

/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c cpu/idt.c -o cpu/idt.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -g -ffreestanding -c cpu/isr.c -o cpu/isr.o

i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel/kernel.o cpu/interrupt.o kernel/util.o drivers/port.o drivers/screen.o cpu/idt.o cpu/isr.o --oformat binary --allow-multiple-definition

cat bootsector.bin kernel.bin > os-image.bin
