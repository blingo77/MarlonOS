[org 0x7c00]

KERNEL_OFFSET equ 0x1000        ;Kernel is placed at memory 0x1000

    mov [BOOT_DRIVE], dl            ; Store dl into BOOT_DRIVE, DL holds the code that represents the Boot drive
                                    ; the BIOS will look into DL for that code. 
    mov bp, 0x9000                  ;base pointer is now 0x9000
    mov sp, bp                      ; stack pointer is now 0x9000 which is where the stack will start

    mov si, REAL_MODE_MSG
    call print
    call print_newline

    call load_kernel    ;reads the kernel fromn the disk
    call switch_to_pm   ; loads GDT, turns off interrupts and jumps to BEGIN_PM
    jmp $

%include "../disk_boot_sect.asm"
%include "../print_boot_sect.asm"
%include "../print_hex_boot.asm"
%include "../32bit_PM/gdt_32bit.asm"
%include "../32bit_PM/print_32bit.asm"
%include "../32bit_PM/switch_32bit.asm"

[bits 16]
load_kernel:
    mov si, LOAD_KERNEL_MSG
    call print
    call print_newline

    mov bx, KERNEL_OFFSET
    mov dh, 2               ; Amount of sectors we want read, and how many that will be passed into load_disk
    mov dl, [BOOT_DRIVE]    ; move dl which got stored in BOOT_DRIVE back into dl
    call load_disk
    ret

[bits 32]
BEGIN_PM:
    mov ebx, PROT_MODE_MSG
    call print_pm
    call KERNEL_OFFSET      ; gives control to the kernel
    jmp $

BOOT_DRIVE db 0 ;we will store dl in here because it dl will be over written, 
                ;the BIOS looks for dl because dl holds the code that represents the drive (HDD, USB DRIVE)
REAL_MODE_MSG db "Starting 16-bit real mode", 0
PROT_MODE_MSG db "Landing in 32bit protected mode", 0
LOAD_KERNEL_MSG db "Loading kernel into memory...", 0

; fill 510 bytes with 0, last two will be 0x55AA (0xAA55 reversed)
times 510 - ($-$$) db 0
dw 0xaa55