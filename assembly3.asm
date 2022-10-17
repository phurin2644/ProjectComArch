li x20, 4
li x21, 5
li x22, 0
li x24, 1
Loop: 
beq x21, x0, Exit
andi x23, x21, 1
beqz  x23 Endif
add x22, x22, x20
Endif:
sll x20, x20, x24
srl x21, x21, x24
beq x0, x0, Loop
Exit: