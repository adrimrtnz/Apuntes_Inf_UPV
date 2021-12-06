                .globl __start
                .text 0x00400000

__start:        li.s $f0, 78.325        # Constante -1.5 
                li.d $f2, 78.325        # Constante 8.75

                li $t0, 0xFF800000    # Menos infinito
                mtc1 $t0, $f12        # Envio a $f12
                li $t0, 0x7F800000    # Mas infinito
                mtc1 $t0, $f14        # Envio a $f14
                li $t0, 0x00000000    # Mas 0
                mtc1 $t0, $f16        # Envio a $f16
                li $t0, 0x80000000    # Menos 0
                mtc1 $t0, $f18        # Envio a $f18
                li $t1, 0x7F8003A0    # Not a Number (NaN)
                mtc1 $t1, $f20        # Envio a $f20

                .end
