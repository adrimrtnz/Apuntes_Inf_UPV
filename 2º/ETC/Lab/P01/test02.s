            .globl __start
            .data 0x1000000A
    var1:   .word 500
    var2:   .word 100
    chain:  .asciiz "practica etc"
            .text 0x00400000

    __start:    la $t0, var1
                la $t1, chain
                lw $s0, 3($t0)
                li $t0, var2
                lw $s1, -4($t0)
                lb $s2, 7($t1)