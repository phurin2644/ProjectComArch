li x20, 2 # mcand
li x21, 4 # mplier
jal x1, Multiply
beq x0, x0, Exit

Multiply:
addi sp,sp,-24
sd x22, 16(sp)
sd x21, 8(sp)
sd x20, 0(sp)
addi x10,x0,0
while_loop: 
beq x21, x0, end_while
    andi x22, x21, 1 
    beqz  x22 Endif
        add x10, x10, x20
    Endif:
    slli x20, x20, 1
    srli x21, x21, 1
    beq x0, x0, while_loop
end_while:

ld x20, 0(sp)
ld x21, 8(sp)
ld x22, 16(sp)
addi sp,sp,24

Exit:
