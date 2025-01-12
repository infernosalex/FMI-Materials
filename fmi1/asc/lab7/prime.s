.section .note.GNU-stack,"",@progbits

.data
    x: .long 0
    div: .long 0
    ans: .long 0
    formatnrprim: .asciz "Yes"
    formatnrnprim: .asciz "No"
    formatScanf: .asciz "%d"
    newLine: .asciz "\n"

.text
prime:
    pushl %ebp                # Save base pointer
    movl %esp, %ebp           # Set base pointer to current stack pointer
    movl 8(%ebp), %eax        # Load the parameter n from the stack into %eax

    # Handle small numbers: if n < 2, it's not prime
    cmpl $2, %eax             # Compare n with 2
    jl .not_prime             # If n < 2, go to not_prime
    je .is_prime              # If n == 2, go to is_prime

    # Set up divisor in %ecx starting from 2
    movl $2, %ecx

# Loop to check divisors from 2 up to sqrt(n)
.check_divisors:
    # Check if n % ecx == 0
    movl %eax, %edx           # Copy n to %edx for division
    xorl %edx, %edx           # Clear %edx for the division remainder
    divl %ecx                 # Divide n by %ecx (n / i), quotient in %eax, remainder in %edx
    testl %edx, %edx          # Check if remainder is zero
    je .not_prime             # If remainder is zero, n is not prime

    # Increment divisor and square it to compare with n
    incl %ecx                 # Increment %ecx (next divisor)
    movl %ecx, %edx           # Copy %ecx to %edx to calculate %ecx * %ecx
    imull %ecx, %edx          # Square %ecx (store result in %edx)
    cmpl 8(%ebp), %edx        # Compare %edx (ecx^2) with n
    jl .check_divisors        # If ecx^2 < n, continue loop

.is_prime:
    movl $1, %eax             # Set return value to 1 (prime)
    jmp .done

.not_prime:
    movl $0, %eax             # Set return value to 0 (not prime)

.done:
    leave                     # Restore base pointer and stack
    ret                       # Return to caller

.global main
main:
    pushl x
    pushl $formatScanf
    call scanf  
    popl %ebx
    popl %ebx


etexit:
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80
