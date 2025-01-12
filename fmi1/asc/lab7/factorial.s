.data
    x: .long 0     
    da: .asciz "Yes\n"
    nu: .asciz "No\n"
    formatScanf: .asciz "%d"
    formatPrintf:.asciz "%d\n"
.text
prime:
    pushl %ebp
    mov %esp, %ebp

    cmpl $2, 8(%ebp)
    jl neprim

    mov $2, %ecx

    prime_loop:
        cmp 8(%ebp), %ecx
        jge prim

        movl 8(%ebp), %eax
        movl $0, %edx
        divl %ecx
        cmp $0, %edx
        je neprim

        incl %ecx
        jmp prime_loop

    prim:
        mov $1, %eax
        jmp prime_exit

    neprim:
        mov $0, %eax

    prime_exit:
        popl %ebp
        ret

factorial:
    pushl %ebp
    mov %esp, %ebp


.global main
main:   
    pushl $x
    pushl $formatScanf
    call scanf
    popl %edx
    popl %edx

    pushl x
    call prime
    popl x

    cmp $1, %eax
    je print_da
    
    push $nu
    call printf
    popl %ebx
    jmp exit

    print_da:
        push $da
        call printf
        popl %ebx 
exit:
    pushl $0
    call fflush
    popl %eax
    
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80