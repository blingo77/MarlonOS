
load_disk:
    pusha

    push dx             ; push dx into stack, dh contains the amt of sectors to read, dl has the drive number

    mov ah, 0x02           ; int 0x13 BIOS 'read' function requires that ah register have 0x02
    mov al, dh             ; move amt of sectors to read into al

    ; CHS (Cylinder, head, sector) even though we wont write it in that order
    mov cl, 0x02           ; cl = the sector, is set to sector 2, sector 1 = boot loader, sector 2 = next available sector
    mov ch, 0x00           ; ch = the cylinder, is set to 0
    mov dh, 0x00           ; dh = the head, is set ti 0

    int 0x13               ; BIOS Interupt
    jc disk_error          ; if the carry flag is set to 1, then jump to disk_error

    pop dx                 ; restore the DX register when we pushed it, giving us back dh = 2, which is the amt of sectors we want read
    cmp al, dh             ; the 0x13 BIOS interrupt will auto store the amt of sectors read into AL register
    jne sector_error       ; if both AL and DH arent ==, then jump to sector error
    popa
    ret

disk_error:

    mov si, DISK_ERROR     ; si will be passed to print
    call print

    call print_newline

    mov dh, ah             ; DH register will recieve AH, AH holds the error code
    call print_hex         ; takes DX as parameter, DH & DL -> DX 
    jmp disk_loop

    ret

sector_error:
    mov si, SECTOR_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "DISK READ ERROR",0
SECTOR_ERROR: db "Wrong # of sectors read", 0
