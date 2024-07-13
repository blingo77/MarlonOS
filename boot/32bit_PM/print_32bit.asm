[bits 32]               ; uses 32-bit protected mode

; in text mode ach character on the screen is represented by two bytes in video memory: 
;one byte for the character code (ASCII) and one byte for the attribute (color, etc.).

VID_MEM equ 0xb8000      ; equ means equals,higher language equvialent to VID_MEM = 0xb800
WHITE_ON_BLACK equ 0x0f ;  

print_pm:
    pusha
    mov edx, VID_MEM    ; store vid_mem address into EDX register

print_pm_loop:

    mov al, [ebx]               ; EBX holds the character so we move it into the lower byte of the AX register
    mov ah, WHITE_ON_BLACK      ; move the color into the high byte of the AX register

    cmp al, 0
    je print_pm_done

    mov [edx], ax       ; store both AH and AL into the video memory address
    add ebx, 1          ; increments the EBX register to move to the next character in the string
    add edx, 2          ; moves to next position in video memory, incremented by two since each char occupies two bytes

    jmp print_pm_loop

print_pm_done:
    popa
    ret
