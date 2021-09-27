        .globl __start
        .data 0x1000000A
var:    .word 26
chain:  .asciiz "coronavirus"
        .text 0x00400000

__start:        la $t0, var
                la $t1, chain
                lw $s0, 0($t0)
                lb $s1, 5($t1)