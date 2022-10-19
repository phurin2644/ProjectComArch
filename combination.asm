li x10, 0
li x11, 5 # n
li x12, 4 # r

Main:
jal x1, combination
beq x0, x0, exit

combination:
addi sp, sp, -40
sd x1, 32(sp)
sd x10,24(sp) 
sd x11,16(sp)
sd x12, 8(sp)
sd x13, 0(sp)
bnez x12, else_r_ne_zero
    beq x0,x0, then_r_eq_zero_or_n_eq_r

else_r_ne_zero:
    bne x11,x12,else_n_ne_r

then_r_eq_zero_or_n_eq_r:
    ld x1, 40(sp)
    li x10, 1
    ld x11,24(sp)
    ld x12,16(sp)
    ld x13, 8(sp)
    ld x14, 0(sp)
    addi sp,sp,48
    jalr x0,0(x1)    
else_n_ne_r:
    addi x11,x11,-1
    jal x1,combination  # combination(n-1,r)
    addi x13,x10,0      # save return value into x13
   
    addi x12,x12,-1
    jal x1,combination # combination(n-1, r-1)
    add x10,x10,x13    # combination(n-1,r) + combination(n-1, r-1)
    
    #restore stack here, except x10
    ld x1, 24(sp)
    ld x11,16(sp)
    ld x12, 8(sp)
    ld x13, 0(sp)
    addi sp, sp, 32
    jalr x0,0,(x1)
   
exit:
    
    

