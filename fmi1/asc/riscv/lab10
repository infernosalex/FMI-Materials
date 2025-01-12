.data
    n: .long 5
    k: .long 2
    v: .long 9, 3, 5, 11, 2
    num: .long 9
    msg1: .string "Numarul "
    msg2: .string " are "
    msg3: .string " divizori: "
    msg4: .string ", "
    msg5: .string "Sunt "
    msg6: .string " elemente cu exact "
    msg7: .string " divizori."
    newline: .string "\n"
.text
.global main
main:
    # call task12
    
    call divizori_elemente
    
    # Ieșire din program
    li a7, 93               # Cod syscall pentru exit
    li a0, 0                # Status de ieșire (0)
    ecall                   # Apel sistem
task12:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    addi s0,sp,0
    
    la a0,msg1
    li a7,4
    ecall    

    
    la a0, num
    lw a0, 0(a0)
    li a7,1
    ecall
        
    la a0,msg2
    li a7,4
    ecall
    
    la a0, num
    lw a0, 0(a0)
    call divizori
    # a0 = nr divizori
    li a7,1
    ecall 
    
    la a0,msg3
    li a7,4
    ecall
    
    la a0, num
    lw a0, 0(a0)
    call divizori_p
    
        
    la a0, num
    lw a0, 0(a0)
    li a7,1
    ecall
    
    lw s0, 0(sp)
    lw ra, 4(sp)
    addi sp,sp,8
    ret
   
divizori:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    addi s0,sp,0

    # a0 = num
    addi s1, a0, 0 # s1 = num
    addi t0,zero,0 # t0 = nr_div
    addi t1,zero,1 # t1 = index
    divizori_loop:
        bgt t1,s1,divizori_end

        rem t2,s1,t1
        bne t2,zero,divizori_loop_continue

        addi t0,t0,1
        addi a0,t1,0
    divizori_loop_continue:
        addi t1,t1,1
        j divizori_loop
    divizori_end:
        addi a0,t0,0
        lw s0, 0(sp)
        lw ra, 4(sp)
        addi sp,sp,8
        ret
        
divizori_p:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    addi s0,sp,0
    
    # a0 = num
    addi s1, a0, 0 # s1 = num
    addi s2, a0, -1
    addi t0,zero,0 # t0 = nr_div
    addi t1,zero,1 # t1 = index
    divizori_p_loop:
        bgt t1,s2,divizori_p_end
        
        rem t2,s1,t1
        bne t2,zero,divizori_p_loop_continue
        
        addi t0,t0,1
        addi a0,t1,0
        li a7,1
        ecall 
        
        la a0,msg4
        li a7,4
        ecall
        
    divizori_p_loop_continue:
        addi t1,t1,1
        j divizori_p_loop
    divizori_p_end:
        addi a0,t0,0     # a0 = nr divizori
        lw s0, 0(sp) 
        lw ra, 4(sp)
        addi sp,sp,8
        ret
 
 divizori_elemente:       
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    addi s0,sp,0 
    
    la a0, n
    lw a0, 0(a0)
    la a5,k
    lw a5,0(a5)
    
    addi s1,a0,0  # s1 n
    addi a1,gp,8 # a1 adresa v
    li a2, 0 # index
    li a3, 0 # nr elemente
    
    divizori_elemente_loop:
        bge a2,s1,divizori_elemente_exit
        
        slli a4,a2,2
        add a4,a4,a1
        lw a4,0(a4) # a4 = elementeul de la adres_v + 4*index = v[index]
        addi a0,a4,0
        call divizori
        bne a0,a5,divizori_elemente_loop_continue
        addi a3,a3,1
        
    divizori_elemente_loop_continue:
        addi a2,a2,1
        j divizori_elemente_loop
    
    divizori_elemente_exit:
        la a0, msg5
        li a7,4
        ecall
        
        addi a0,a3,0
        li a7,1
        ecall 
        
        la a0, msg6
        li a7,4
        ecall
        
        addi a0,a5,0
        li a7,1
        ecall
        
        la a0, msg7
        li a7,4
        ecall
        
        lw s0, 0(sp)
        lw ra, 4(sp)
        addi sp,sp,8
        ret 