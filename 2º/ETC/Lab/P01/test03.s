            .globl __start
            .data 0x10000008
    A:      .word 2000
    B:      .byte 190
    C:      .byte 210
    Delta:  .word 12000
            .text 0x00400000

    __start:    la $t0, 0x10001010
                lw $t1, 0($t0)