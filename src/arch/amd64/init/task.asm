start_task:
    xchg bx, bx
    mov esp, rdi

    pop rbx
    mov cr4, rbx
    pop rbx
    mov cr3, rbx
    pop rbx
    mov cr2, rbx
    pop rbx
    mov cr0, rbx

    ; Pop all registers
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; Pop int no and error code
    add esp, 16

    iretq