global _gdt_reload_segments
_gdt_reload_segments:
    ; Data segment
    mov ax, 16
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ret