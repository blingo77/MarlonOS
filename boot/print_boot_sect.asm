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

print_newline:
    mov ah, 0eh
    mov al, 0x0a        ; a newline charachter, moves cursor down to next line
    int 0x10            

    mov al, 0x0d        ; carriage return. move cursor to the beginning of line
    int 0x10

    ret