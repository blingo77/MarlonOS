start_gdt:

    null_descriptor:
        ; the GDT starts will a null 8 bytes
        dd 0x0
        dd 0x0
    
    code_descriptor:
        dw 0xffff    ; segment length, bits 0-15
        dw 0x0       ; segment base, bits 0-15
        db 0x0       ; segment base, bits 16-23
        db 10011010b ; flags (8 bits)
        db 11001111b ; flags (4 bits) + segment length, bits 16-19
        db 0x0       ; segment base, bits 24-31
    
    data_descriptor:
        dw 0xffff
        dw 0x0
        db 0x0
        db 10010010b
        db 11001111b
        db 0x0
end_gdt:

gdt_descriptor:
    dw gdt_end - start_gdt - 1
    dd get_start

CODE_SEGMENT equ code_descriptor - start_gdt
DATA_SEGMENT equ data_descriptor - start_gdt