extern tasking_current_task
extern scheduler_switch_task
extern k_tss

; Note: All of the following must be mapped in a process
; - This function
; - Kernel stack
; - tasking_current_task
; - tasking_kernel_cr3

; Mark beginning, used to map the context switching code in processes
global tasking_ctx_switch_begin
tasking_ctx_switch_begin:

global tasking_kernel_cr3
tasking_kernel_cr3:
    dq 0

; Normal task switch, called when yielding
global tasking_ctx_switch
tasking_ctx_switch:
    push rax
    push rbx
    mov rax, [tasking_kernel_cr3]
    mov rbx, cr3
    cmp rbx, rax
    je tasking_ctx_switch_main

    ; Switch back to kernel CR3
    mov cr3, rax
    jmp tasking_ctx_switch_main

; Interrupt task switch, called by timer
global tasking_ctx_switch_int
tasking_ctx_switch_int:
    push rax
    push rbx
    mov rax, [tasking_kernel_cr3]
    mov rbx, cr3
    cmp rbx, rax
    je tasking_no_cr3_change_int

    ; Switch back to kernel CR3
    mov cr3, rax

tasking_no_cr3_change_int:
    ; Signal to the PIC
    mov al, 0x20
    out 0x20, al

; Main part of the context switching code
tasking_ctx_switch_main:
    mov rax, [tasking_current_task]

    ; Save all register except RAX
    mov [rax + 0], r15
    mov [rax + 8], r14
    mov [rax + 16], r13
    mov [rax + 24], r12
    mov [rax + 32], r11
    mov [rax + 40], r10
    mov [rax + 48], r9
    mov [rax + 56], r8
    mov [rax + 64], rdi
    mov [rax + 72], rsi
    mov [rax + 80], rbp
    mov [rax + 88], rdx
    mov [rax + 96], rcx

    ; Save CR3
    mov [rax + 120], rbx

    ; Save RBX
    pop rbx
    mov [rax + 104], rbx

    ; Save RAX
    pop rbx
    mov [rax + 112], rbx

    ; Save rip, cs, rflags, rsp and ss
    mov rbx, [rsp] ; RIP
    mov [rax + 128], rbx

    mov rbx, [rsp + 8] ; CS
    mov [rax + 136], rbx

    mov rbx, [rsp + 16] ; RFLAGS
    mov [rax + 144], rbx

    mov rbx, [rsp + 24] ; RSP
    mov [rax + 152], rbx

    mov rbx, [rsp + 32] ; SS
    mov [rax + 160], rbx

    ; Load next task (with C handler)
    call scheduler_switch_task
    mov rax, [tasking_current_task]

    ; Load new stack in TSS if the new task is not in ring 0
    mov bl, [rax + 176]
    cmp bl, 0
    je tasking_no_set_tss_stack

    mov rbx, [rax + 168]
    mov [k_tss + 4], rbx

tasking_no_set_tss_stack:
    ; If the address space changes, switch to it and get task's stack
    mov rbx, [rax + 120]
    cmp rbx, [tasking_kernel_cr3]
    je tasking_end_no_cr3_change

    ; Set pml4
    mov cr3, rbx

    ; Switch to stack and push 5 (40 bytes) fake values (will be filled out later)
    mov rsp, [rax + 152]
    sub rsp, 40

tasking_end_no_cr3_change:


    ; Load GP registers
    mov r15, [rax + 0]
    mov r14, [rax + 8]
    mov r13, [rax + 16]
    mov r12, [rax + 24]
    mov r11, [rax + 32]
    mov r10, [rax + 40]
    mov r9, [rax + 48]
    mov r8, [rax + 56]
    mov rdi, [rax + 64]
    mov rsi, [rax + 72]
    mov rbp, [rax + 80]
    mov rdx, [rax + 88]
    mov rcx, [rax + 96]

    ; Save rax and rbx on the stack
    mov rbx, [rax + 104]
    push rbx

    mov rbx, [rax + 112]
    push rbx

    ; Load iret stack frame (mind the 16 byte offset because of rax and rbx)
    mov rbx, [rax + 128]
    mov [rsp + 16], rbx ; RIP

    mov rbx, [rax + 136]
    mov [rsp + 24], rbx ; CS

    mov rbx, [rax + 144]
    mov [rsp + 32], rbx ; RFLAGS

    mov rbx, [rax + 152]
    mov [rsp + 40], rbx ; RSP

    mov rbx, [rax + 160]
    mov [rsp + 48], rbx ; SS

    ; Load rax and rbx
    pop rax
    pop rbx

    ; Load segments
    mov ds, [rsp + 32]
    mov es, [rsp + 32]
    mov fs, [rsp + 32]
    mov gs, [rsp + 32]

    ; And we're done :)
    ; Note: no need to sti since the flags will take care of that
    iretq

; Mark end, used to map the context switching code in processes
global tasking_ctx_switch_end
tasking_ctx_switch_end:



global tasking_dummy_isr_test
tasking_dummy_isr_test:
    ;xchg bx, bx
    push rax
    mov al, 0x20
    out 0x20, al
    pop rax
    iretq