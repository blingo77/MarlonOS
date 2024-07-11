[org 0x7c00]                        ; set origin 0x7c00
BITS 16                             ;instructions will be generated in 16-bit instructions


start:

    mov si, message                 ; sets the message mem adress into si register
    call print                      ; calls sub routine print which is in file ./print_boot_sect.asm

    call print_newline              ; prints new line, in same file as print

    mov si, GOODBYE
    call print

    call print_newline

    mov dx, 0x12fe
    call print_hex

    jmp $
    
%include "./print_boot_sect.asm"    ; includes the file that has print function
%include "./print_hex_boot.asm"

message: 
    db 'hello World', 0
GOODBYE:
    db 'Goodbyte!', 0

times 510-($ - $$) db 0             ; fills the rest of the 512 byte sector with zeroes
dw 0xAA55                           ; will be flipped as 0x55AA and is placed at the end of the 512 byte sector, dw is two bites