### PROGRAMA BASE PRACTICAS DE ENTRADA/SALIDA MIPS R2000

#-------------------------------------------------#
#
#  PRÁCTICA 12: SINCRONIZACIÓN POR PRUEBA DE ESTADO
# 
#-------------------------------------------------#


#------- Segmento de datos ---------#
	.data		
T1:	.asciiz "Esperando...\n"
T2:	.asciiz "\nFin\n"
CHAR: .byte 0

#------- Segmento de código ---------#
	.text
    	.globl __start	

__start:
	# Escribe en consola mensaje T1
	li $v0, 4
	la $a0, T1
	syscall	
	
	# Carga dir base teclado
	la $t0, 0xffff0000

	# Carga código ASCII de la tecla ESC
	li $s0, 27

espera: # Espera bit R == 1
	lw $t1,0($t0)
	andi $t1,$t1,1
	beqz $t1,espera

### Lee el registro de datos del teclado, leer este registro provoca R=0	
	lw $t2,4($t0)

	li $t3, 0xFF
	and $t2, $t2, $t3
	beq $t2,$s0,salida # Comprueba si se ha pulsado la tecla ESC

	sw $t2, CHAR
	li $v0, 4 	# print char
	la $a0, CHAR
	syscall
	j espera


salida:	# Si se ha pulsado 'ESC' -> Escribe en consola mensaje T2
	li $v0, 4
	la $a0, T2
	syscall

	# exit
	li $v0, 10
	syscall			

	.end