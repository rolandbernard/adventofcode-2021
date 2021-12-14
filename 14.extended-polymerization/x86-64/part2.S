
.data
result: .ascii "Result: "

.bss
freq: .zero 208
pairs: .zero 5408
x: .zero 8
instr: .zero 2028
instr_count: .zero 8
buffer: .zero 5408

.text
.global _start

read_char:
    mov $1, %rdx
    lea buffer, %rsi
    mov $0, %rdi
    mov $0, %rax
    syscall
    mov buffer, %rax
    ret

read_instr:
    mov $8, %rdx
    lea buffer, %rsi
    mov $0, %rdi
    mov $0, %rax
    syscall
    sub %rax, %rdx
    add %rax, %rsi
    cmp $0, %rdx
    je .loop_read_instr_exit
    cmp $0, %rax
    jne read_instr
    mov $0, %rax
    ret
.loop_read_instr_exit:
    mov $1, %rax
    ret

read_input:
    call read_char
    sub $65, %rax
    addq $1, freq(,%rax,8)
    mov %rax, %rbx
.loop_pol_start:
    call read_char
    cmp $10, %rax
    je .loop_pol_exit
    sub $65, %rax
    addq $1, freq(,%rax,8)
    imul $208, %rbx
    addq $1, pairs(%rbx,%rax,8)
    mov %rax, %rbx
    jmp .loop_pol_start
.loop_pol_exit:
.loop_in_instr_start:
    call read_instr
    cmp $0, %rax
    je .loop_in_instr_exit
    mov instr_count, %rax
    imul $3, %rax
    lea buffer, %rbx
    inc %rbx

    mov $0, %rcx
    mov (%rbx), %cl
    sub $65, %rcx
    mov %rcx, instr(%rax)
    inc %rax
    inc %rbx

    mov (%rbx), %cl
    sub $65, %rcx
    mov %rcx, instr(%rax)
    inc %rax
    add $5, %rbx

    mov (%rbx), %cl
    sub $65, %rcx
    mov %rcx, instr(%rax)
    inc %rax

    addq $1, instr_count
    jmp .loop_in_instr_start
.loop_in_instr_exit:
    ret

memcpy:
.loop_outer_copy_start:
    cmp $0, %rcx
    je .loop_outer_copy_exit
    mov (%rbx), %dl
    mov %dl, (%rax)
    inc %rax
    inc %rbx
    dec %rcx
    jmp .loop_outer_copy_start
.loop_outer_copy_exit:
    ret

apply_instr:
    lea buffer, %rax
    lea pairs, %rbx
    mov $5408, %rcx
    call memcpy
    mov $0, %rdi
.loop_instr_start:
    cmp instr_count, %rdi
    je .loop_instr_exit

    mov %rdi, %rax
    imul $3, %rax
    mov $0, %rbx
    mov instr(%rax), %bl
    inc %rax
    mov $0, %rcx
    mov instr(%rax), %cl
    inc %rax
    mov $0, %rdx
    mov instr(%rax), %dl

    imul $208, %rbx
    mov pairs(%rbx,%rcx,8), %r8

    add %r8, freq(,%rdx,8)
    sub %r8, buffer(%rbx,%rcx,8)
    add %r8, buffer(%rbx,%rdx,8)
    imul $208, %rdx
    add %r8, buffer(%rdx,%rcx,8)

    inc %rdi
    jmp .loop_instr_start
.loop_instr_exit:
    lea pairs, %rax
    lea buffer, %rbx
    mov $5408, %rcx
    call memcpy
    ret

compute_result:
    mov $0, %rax
    mov $9223372036854775807, %rbx
    mov $0, %rdi
.loop_count_start:
    cmp $26, %rdi
    je .loop_count_exit
    cmpq $0, freq(,%rdi,8)
    je .not_min
    cmp %rbx, freq(,%rdi,8)
    jg .not_min
    mov freq(,%rdi,8), %rbx
.not_min:
    cmp %rax, freq(,%rdi,8)
    jl .not_max
    mov freq(,%rdi,8), %rax
.not_max:
    inc %rdi
    jmp .loop_count_start
.loop_count_exit:
    sub %rbx, %rax
    ret

output_result:
    mov %rax, %r8
    mov $8, %rdx
    lea result, %rsi
    mov $1, %rdi
    mov $1, %rax
    syscall
    mov %r8, %rax
    mov $0, %r9
.loop_print_start:
    mov $0, %rdx
    mov $10, %r8
    idiv %r8
    add $48, %rdx
    mov %rdx, buffer(%r9)
    inc %r9
    cmp $0, %rax
    jne .loop_print_start
.loop_print_exit:
    mov $0, %r8
    mov %r9, %r10
.loop_rev_start:
    dec %r10
    cmp %r10, %r8
    jge .loop_rev_exit
    mov buffer(%r10), %r11b
    mov buffer(%r8), %r12b
    mov %r11b, buffer(%r8)
    mov %r12b, buffer(%r10)
    inc %r8
    jmp .loop_rev_start
.loop_rev_exit:
    movb $10, buffer(%r9)
    inc %r9
    mov %r9, %rdx
    lea buffer, %rsi
    mov $1, %rdi
    mov $1, %rax
    syscall
    ret

_start:
    call read_input
    mov $0, %r9
.loop_start:
    cmp $40, %r9
    jge .loop_exit
    call apply_instr
    inc %r9
    jmp .loop_start
.loop_exit:
    call compute_result
    call output_result
    mov $0, %rdi
    mov $60, %rax
    syscall

