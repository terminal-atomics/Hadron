bits 32

MAGIC       equ     0x1BADB002
FLAGS       equ     3
CHECKSUM    equ     -(MAGIC + FLAGS)

section .multiboot
align 8

global _kernel_code_start
_kernel_code_start:

dd MAGIC
dd FLAGS
dd CHECKSUM

section .bss
align 0x1000

; Stack
_stack_bottom:
resb 0x1000
_stack_top:

; Page directory pointer table
_temp_pdpt:
resb 0x1000
_temp_pdpt_end:

; Level 4 tabme
_temp_pml4t:
resb 0x1000

section .text
global _start
_start:
    ; Disable interrupts
    cli

    ; Setup the stack
    mov esp, _stack_top

    ; Save multiboot and push dummy bytes since we pop 64 bits at a time
    push dword 0
    push ebx
    push dword 0
    push eax

    ; Clear paging tables
    xor eax, eax
    mov ebx, 0x2000

    mov esi, _temp_pdpt
    call _memset

    ; Fill both page tables
    mov eax, 0b10000011 ; Flags
    xor ebx, ebx
    mov esi, _temp_pdpt
    clc
_pdp_fill_loop:
    mov [esi], eax
    mov [esi + 4], ebx
    add esi, 8
    add eax, 0x40000000
    jnc _pdp_fill_no_carry
    inc ebx
_pdp_fill_no_carry:
    cmp esi, _temp_pdpt_end
    jl _pdp_fill_loop

    ; Fill PML4T
    mov eax, _temp_pdpt
    or eax, 0b11 ; Flags
    mov [_temp_pml4t], eax

    ; Set CR3 to the pmlt4
    mov eax, _temp_pml4t
    mov cr3, eax

    ; Enable PAE
    mov eax, cr4
    or eax, (1 << 5) ; Firth bit is PAE
    mov cr4, eax 

    ; Enable Long Mode
    mov ecx, 0xC0000080 ; EFER Model Specific Register
    rdmsr
    or eax, (1 << 8) ; Set the LM-bit which is the 9th bit (bit 8).
    wrmsr

    ; Enable Paging
    mov eax, cr0
    or eax, (1 << 31)
    mov cr0, eax

    ; Load temporart GDT
    lgdt [_temp_gdt64.ptr]

    ; Jmp to long mode init
    jmp _temp_gdt64.code:_long_mode_init

_memset:
    pusha
    add ebx, esi
_memset_loop:
    mov [esi], al
    inc esi
    cmp ebx, esi
    jne _memset_loop
    popa
    ret

bits 64
extern _init
_long_mode_init:
    cli

    ; Get multiboot info back from the stack and convert to 64bit
    xor rax, rax
    xor rbx, rbx
    pop rax
    pop rbx
    mov rdi, rax
    mov rsi, rbx

    xor rbp, rbp
    call _init

_end:
    jmp _end

section .data
_temp_gdt64:                           ; Global Descriptor Table (64-bit).
    .null: equ $ - _temp_gdt64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .code: equ $ - _temp_gdt64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .data: equ $ - _temp_gdt64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .ptr:                    ; The GDT-pointer.
    dw $ - _temp_gdt64 - 1             ; Limit.
    dq _temp_gdt64                     ; Base.

section .size_detect
global _kernel_code_end
_kernel_code_end: