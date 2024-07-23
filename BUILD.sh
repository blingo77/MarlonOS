#!/usr/bin/bash

# create bootsector.bin and move to main directory
cd boot/main

make bootsector.bin

mv bootsector.bin ../..
cd ../..

#kernel.o
i386-elf-gcc -ffreestanding -c kernel/kernel.c -o kernel.o
mv kernel.o ./kernel/

#turn drivers into object files
i386-elf-gcc -ffreestanding -c drivers/port.c -o port.o
i386-elf-gcc -ffreestanding -c drivers/screen.c -o screen.o

mv port.o ./drivers/
mv screen.o ./drivers/

#kernel_entry.o
nasm kernel/kernel_entry/kernel_entry.asm -f elf -o kernel_entry.o

#link kernel.o and kernel_entry.o into kernel.bin
i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel/kernel.o drivers/port.o drivers/screen.o --oformat binary

#catnate kernel.bin and bootsector.bin
cat bootsector.bin kernel.bin > os-image.bin
