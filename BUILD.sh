#!/usr/bin/bash

# create bootsector.bin and move to main directory
cd boot/main

make bootsector.bin

mv bootsector.bin ../..
cd ../..

#kernel.o
i386-elf-gcc -ffreestanding -c kernel/kernel.c -o kernel.o
mv kernel.o ./kernel/

#turn drivers and other files into object files
i386-elf-gcc -ffreestanding -c drivers/port.c -o port.o
i386-elf-gcc -ffreestanding -c drivers/screen.c -o screen.o
i386-elf-gcc -ffreestanding -c kernel/util.c -o util.o
i386-elf-gcc -ffreestanding -c cpu/idt.c -o idt.o
i386-elf-gcc -ffreestanding -c cpu/isr.c -o isr.o

# moves object files to original files
mv port.o ./drivers/
mv screen.o ./drivers/
mv util.o ./kernel/
mv idt.o ./cpu/
mv isr.o ./cpu/

#kernel_entry.o
nasm kernel/kernel_entry/kernel_entry.asm -f elf -o kernel_entry.o

nasm cpu/interrupt.asm -f elf -o interrupt.o

#link kernel.o, kernel_entry.o and other object files into kernel.bin
i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o interrupt.o kernel/kernel.o drivers/port.o drivers/screen.o kernel/util.o --oformat binary --allow-multiple-definition

#catnate kernel.bin and bootsector.bin
cat bootsector.bin kernel.bin > os-image.bin
