[org 0x7c00]                        ; set origin 0x7c00
BITS 16                             ;instructions will be generated in 16-bit instructions


start:

    mov bp, 0x8000                  ; set the stack at 0x8000 which moves it safely away from us
    mov sp, bp                      ; sets stack pointer to base pointer, making stack start at 0x8000

    mov bx, 0x9000                  ;sets destination buffer to read at segment 0x0000, offset 0x9000 es:bx = 0x0000:0x9000 = 0x9000
    mov dh, 2                       ; number of sectors to read
    call load_disk

    mov dx, [0x9000]                ; call first loaded sector, 0xdada
    call print_hex                  ; dx is passed into print_hex

    call print_newline

    mov dx, [0x9000 + 512]          ; add 512 bytes giving us the second loaded sector, 0xface
    call print_hex

    jmp $
    
%include "./print_boot_sect.asm"    ; includes the file that has print function
%include "./print_hex_boot.asm"
%include "./disk_boot_sect.asm"

message: 
    db 'hello World', 0
GOODBYE:
    db 'Goodbyte!', 0

times 510-($ - $$) db 0             ; fills the rest of the 512 byte sector with zeroes
dw 0xAA55                           ; will be flipped as 0x55AA and is placed at the end of the 512 byte sector, dw is two bites

;boot sector = sector 1
times 256 dw 0xdada ; sector 2 = 512 bytes, when booting this sector it will print 0xdada
times 256 dw 0xface ; sector 3 = 512 bytes, when booting this sector it will print 0xface