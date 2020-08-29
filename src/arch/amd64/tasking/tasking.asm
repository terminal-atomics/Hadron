section .bss
_test_stack_bottom:
resb 0x1000
_test_stack_top:

section .text
extern k_tss
global tasking_enter_r3
tasking_enter_r3:
    xchg bx, bx

    ; Save kernel stack on TSS
    mov [k_tss + 4], esp

    mov ax, 0x20 | 0b11
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax

    push qword 0x20 | 0b11  ; Code segment
    push _test_stack_top    ; Stack pointer
    push qword 0            ; Flags
    push qword 0x18 | 0b11  ; 
    push _test_r3_task
    iretq

global _test_r3_task
_test_r3_task:
    int 0x42
    jmp _test_r3_task
