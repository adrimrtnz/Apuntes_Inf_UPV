ori r8,r0,#20

etq:           lw r7,0(r4)

sub r6,r6,r7

addi r4,r4,#4

addi r8,r8,#-1

j etq