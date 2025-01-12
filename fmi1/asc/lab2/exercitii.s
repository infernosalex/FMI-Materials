.data
    x: .long 65
    y: .long 10
    ec1: .space 4
    ec2: .space 4
.text
.global main
main:
    mov x, %eax
    mov $3, %ebx
    mul %ebx
    mov %eax, ec1
    
    mov y, %eax
    mov $2, %ebx
    mul %ebx
    add %eax, ec1

    mov y, %eax
    sub $3, %eax
    mov %eax, %ecx

    mov x, %eax
    div %ecx
    mov %edx, ec2

iesire:
    mov $1, %eax
    mov $0, %ebx
    int $0x80
