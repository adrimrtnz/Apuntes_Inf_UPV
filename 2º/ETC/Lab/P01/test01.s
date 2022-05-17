. data = 0x1000000C
var1: .word 500
var2: .word 100
cadena: .asciiz “practica etc”


la $t0, var1
la $t1, cadena
lw $s0, 3($t0)
li $t0, var2
lw $s1, -4($t0)
lb $s2, 7($t1)