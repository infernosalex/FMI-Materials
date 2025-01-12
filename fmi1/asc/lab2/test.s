.data
    nume: .space 9
.text
.global main
main:
    mov $3, %eax
    mov $0, %ebx
    mov $nume, %ecx
    mov $9, %edx
    int $0x80

    mov $4, %eax
    mov $1, %ebx
    mov $nume, %ecx
    mov $9, %edx
    int $0x80

    mov $1, %eax
    mov $0, %ebx
    int $0x80
    