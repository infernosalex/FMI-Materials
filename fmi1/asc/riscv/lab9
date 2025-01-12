.data    
    rezultat: .long 0
    num:    .long 5                        # Declarația unui întreg
    name:   .asciz "Hello world, RISC-V!\n" # Declarația unui string
    a: .long 7                             # Variabilă a
    b: .long 8                             # Variabilă b
    c: .long 10
    d: .long 3
    exp: .asciz "Rezultatul expresiei este: "
    
.text
.global main

main:
    # Afișare string
    la a0, name                  # Încarcă adresa lui 'name' în a0
    li a7, 4                    # Apel de sistem pentru afișarea unui string (RISC-V syscall pentru Linux)
    ecall                        # Apel sistem


    # Afișare valori inițiale ale lui a și b
    la a0, a                     # Încarcă adresa lui 'a' în a0
    lw a0, 0(a0)                 # Încarcă valoarea lui 'a' în a0
    li a7, 1                     # Cod pentru sys_write (afișare întreg)
    ecall                        # Apel sistem pentru afișare

    la a0, b                     # Încarcă adresa lui 'b' în a0
    lw a0, 0(a0)                 # Încarcă valoarea lui 'b' în a0
    li a7, 1                     # Cod pentru sys_write (afișare întreg)
    ecall                        # Apel sistem pentru afișare

    # Apel funcție de interschimbare
    la a0, a                     # Încarcă adresa lui 'a' în a0
    la a1, b                     # Încarcă adresa lui 'b' în a1
    call swap                    # Apel funcția de interschimbare

    # Afișare valori după interschimbare
    la a0, a                     # Încarcă adresa lui 'a' în a0
    lw a0, 0(a0)                 # Încarcă valoarea lui 'a' în a0
    li a7, 1                     # Cod pentru sys_write (afișare întreg)
    ecall                        # Apel sistem pentru afișare
    
    la a0, b                     # Încarcă adresa lui 'b' în a0
    lw a0, 0(a0)                 # Încarcă valoarea lui 'b' în a0
    li a7, 1                     # Cod pentru sys_write (afișare întreg)
    ecall                        # Apel sistem pentru afișare


    la a0, a                     # Încarcă adresa lui 'a' în a0
    la a1, b                     # Încarcă adresa lui 'b' în a1
    la a2, c
    la a3, d
    call expresie

    # Ieșire din program
    li a7, 93                    # Cod pentru sys_exit
    li a0, 0                     # Statusul de ieșire
    ecall                        # Apel sistem

# Funcție de interschimbare
# Argumente:
# a0 = adresa lui 'a'
# a1 = adresa lui 'b'
swap:
    # Salvare registre
    addi sp, sp, -16 
    sw ra, 12(sp)

    # Încarcă valorile în registre temporare
    lw t0, 0(a0)                 # t0 = valoarea lui 'a'
    lw t1, 0(a1)                 # t1 = valoarea lui 'b'

    # Interschimbare
    sw t1, 0(a0)                 # 'a' = t1 (valoarea lui 'b')
    sw t0, 0(a1)                 # 'b' = t0 (valoarea lui 'a')

    # Restaurare registre
    lw ra, 12(sp)
    addi sp, sp, 16
    ret                          # Revenire la apelant

expresie:
    addi sp, sp, -32
    sw ra, 16(sp)
    
    lw t0, 0(a0)
    lw t1, 0(a1)
    lw t2, 0(a2)
    lw t3, 0(a3)
    li t4, 0 # t4 = 0 
     
    add t4,t0,t1 # t4 = a + b
    addi t4, t4, 5 # t4 = a + b + 5
    slli t4,t4,1 # t4 = (a + b + 5)*2
    sll t4,t4,t2 # t4 = ((a + b + 5)*2)<<c
    or t4,t4,t3 # t4 = ((((a + b + 5)*2)<<c)|d)
    
    la a0,exp
    li a7,4
    ecall
    
    # sw t4,0(gp)
    # la a0, rezultat
    # lw a0, 0(a0)
    addi a0,t4,0 # move a0, t4
    li a7, 1
    ecall
    
    lw ra, 16(sp)
    addi sp, sp, 32
    ret

# encode and t0,s1,a5
# funct7  rs2   rs1   funct3   rd    opcode
# 0000000 01111 01001 111      00101 0110011