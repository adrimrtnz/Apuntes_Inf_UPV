
ori r8,r0,#20
ori  r7,r7,#0xFFFF
nop
nop
ori  r7,r7,#0xFFFF
lw  r4,0(r8)
nop
nop
add r6,r6,r4
sw  0(r8),r7
addi r8,r8,#-4
nop
nop
andi r1,r8,#0x3A
trap #0