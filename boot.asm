[org 0x7c00]            ; set origin 0x7c00
BITS 16                 ;instructions will be generated in 16-bit instructions

jmp 0x7c0: start

start:

    mov si, message     ; sets the message mem adress into si register
    call print          ;   calls sub routine print

    jmp $
    
print:
    mov bx, 0           ; sets bx to 0 for the page number in browns interupt list
    mov ah, 0eh         ; the function code that tells the computer to display a char on the screen 
.loop_head:

    lodsb               ;looks into the si register and will load each charchter into the al register

    cmp al, 0           ; compare al and 0, if both are zero that means you reached the end of the string
    je .done            ; if al and 0 are equal then it jumps to .done
    
    call printChar      ; goes to printChar routine
    jmp .loop_head      ; jumps back to the top op loop_head

.done:
    ret

printChar:
  
  int 0x10              ; Has to be called everytime a new char will be displayed, this is the interrupt, the BIOS video service interrupt
  ret

message: db 'hello World', 0

times 510-($ - $$) db 0 ; fills the rest of the 512 byte sector with zeroes
dw 0xAA55               ; will be flipped as 0x55AA and is placed at the end of the 512 byte sector, dw is two bites