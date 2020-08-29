extern scheduler_current_task
extern scheduler_kernel_cr3

; Note: All of the following must be mapped in a process
; - This function
; - Kernel stack
; - scheduler_current_task
; - scheduler_kernel_cr3

global scheduler_yield_handler
scheduler_yield_handler:
    push rax
    push rbx
    mov rax, [scheduler_kernel_cr3]
    mov rbx, cr3
    cmp rbx, rax
    je scheduler_no_cr3_change

    ; Switch back to kernel CR3
    mov cr3, rax

scheduler_no_cr3_change:
    mov rax, [scheduler_current_task]

    ; Save all register except RAX
    mov [rax + 16], r15
    mov [rax + 24], r14
    mov [rax + 32], r13
    mov [rax + 40], r12
    mov [rax + 48], r11
    mov [rax + 56], r10
    mov [rax + 64], r9
    mov [rax + 72], r8
    mov [rax + 80], rdi
    mov [rax + 88], rsi
    mov [rax + 96], rbp
    mov [rax + 104], rdx
    mov [rax + 112], rcx

    ; Save CR3
    mov [rax + 136], rbx

    ; Save RBX
    pop rbx
    mov [rax + 120], rbx

    ; Save RAX
    pop rbx
    mov [rax + 128], rbx

    ; Save rip, cs, rflags, rsp and ss
    mov rbx, [rsp] ; RIP
    mov [rax + 144], rbx

    mov rbx, [rsp + 8] ; CS
    mov [rax + 152], rbx

    mov rbx, [rsp + 16] ; RFLAGS
    mov [rax + 160], rbx

    mov rbx, [rsp + 24] ; RSP
    mov [rax + 168], rbx

    mov rbx, [rsp + 32] ; SS
    mov [rax + 176], rbx

    ; Load next task (could replace with C handler)
    mov rbx, [rax]
    mov [scheduler_current_task], rbx
    mov rax, rbx

    ; Load GP registers
    mov r15, [rax + 16]
    mov r14, [rax + 24]
    mov r13, [rax + 32]
    mov r12, [rax + 40]
    mov r11, [rax + 48]
    mov r10, [rax + 56]
    mov r9, [rax + 64]
    mov r8, [rax + 72]
    mov rdi, [rax + 80]
    mov rsi, [rax + 88]
    mov rbp, [rax + 96]
    mov rdx, [rax + 104]
    mov rcx, [rax + 112]

    ; Save rax and rbx on the stack
    mov rbx, [rax + 120]
    push rbx

    mov rbx, [rax + 128]
    push rbx

    ; Load iret stack frame (mind the 16 byte offset because of rax and rbx)
    mov rbx, [rax + 144]
    mov [rsp - 16], rbx ; RIP

    mov rbx, [rax + 152]
    mov [rsp - 24], rbx ; CS

    mov rbx, [rax + 160]
    mov [rsp - 32], rbx ; RFLAGS

    mov rbx, [rax + 168]
    mov [rsp - 40], rbx ; RSP

    mov rbx, [rax + 176]
    mov [rsp - 48], rbx ; SS

    ; Check if CR3 needs to change
    mov rbx, [rax + 136]
    cmp rbx, [scheduler_kernel_cr3]
    je scheduler_end_no_cr3_change

    mov cr3, rbx

scheduler_end_no_cr3_change:
    ; Load rax and rbx
    pop rax
    pop rbx

    ; And we're done :)
    iret
