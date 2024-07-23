# $@ -> target file
# $< -> first dependency
# $^ -> all dependenceis
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

CFLAGS = -g

# C Compiler
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

# catnate into one binary file
os-image.bin: bootsector.bin kernel.bin
	cat $^ > $@

qemu-run: os-image.bin
	sudo qemu-system-i386 -drive format=raw,file=os-image.bin

# links together kernel.c and kernel_entry.asm Object files
kernel.bin: kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# creates kernel object file
kernel.o: kernel/kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

# creates kernel_entry object file
kernel_entry.o : kernel/kernel_entry/kernel_entry.asm 
	nasm $< -f elf -o $@

#disassembles kernel
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

kernel.elf: kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

#rules for wildcare
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.o *.dis os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o