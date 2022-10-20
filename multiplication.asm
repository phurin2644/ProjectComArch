li a0 2 # mcand
li a1,4 # mplier
jal x1, Multiply
beq x0, x0, Exit

Multiply:
addi sp,sp,-56
sd a6, 48(sp)
sd a5, 40(sp)
sd a4, 32(sp)
sd a3, 24(sp)
sd a2, 16(sp)
sd a1, 8(sp) # mplier
sd a0, 0(sp) # mcand
addi a7,a7,0
#x23 = 1;
la a, oneBit
li a4 0x8000
li a5, 1
li t0, 0
while_loop: 
beq a3, a4 end_while 

    #x6 = x3 and x5 
    and a6, a1, a3
    beq a6, t0 end_if
        add a7, a7, a0
    end_if:
    #slli
    add a0 , a0 , a0
    #srli
    #x23 = x23 + x23
    add a3, a3, a3
    
    beq x0, x0, while_loop
end_while:

ld a0, 0(sp)
ld a1, 8(sp)
ld a2, 16(sp)
ld a3, 24(sp)
ld a4, 32(sp)
ld a5, 40(sp)
ld a6, 48(sp)
addi sp,sp,56

Exit:
