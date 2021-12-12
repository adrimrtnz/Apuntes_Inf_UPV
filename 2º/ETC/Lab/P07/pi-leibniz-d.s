                ##########################################################
                # Segmento de datos
                ##########################################################

                .data 0x10000000
cad_entrada:    .asciiz "\nDime el numero de iteraciones: "
cad_salida:     .asciiz "El valor calculado de pi es: " 

                ##########################################################
                # Segmento de c�digo
                ##########################################################

                .globl __start
                .text 0x00400000
__start:        
                ########################################################
                # Lectura del n�mero de iteraciones
                ########################################################

                la $a0, cad_entrada     # Cadena a imprimir
                li $v0, 4               # Funci�n print_string
                syscall

                li $v0, 5               # Funci�n read_int
                syscall

                move $a0, $v0           # Par�metro de la subrutina
                jal leibniz             # Salto a la subrutina

                ########################################################
                # Impresi�n del resultado
                ########################################################

                la $a0, cad_salida      # Cadena a imprimir
                li $v0, 4               # Funci�n print_string
                syscall

                li $v0, 2               # Funci�n print_float
                mfc1 $t0, $f0           # Valor a imprimir
                mtc1 $t0, $f12
                syscall

                ########################################################
                # Finalizaci�n del programa 
                # Llamada al sistema denominada "exit"
                ########################################################= 

                li $v0, 10
                syscall
                
                ########################################################
                # C�lculo de pi con el m�todo de Leibniz
                # $a0 = N�mero de iteraciones de la serie
                ########################################################

leibniz:        li.d $f0, 0.0           # Constante 0.0
                li.d $f4, 1.0           # Constante 1.0
                li.d $f6, 2.0           # Constante 2.0
                move $t0, $a0           # Contador n�mero de iteraciones

bucle:          mtc1 $t0, $f8           # Lleva n a la FPU
                cvt.d.w $f8, $f8        # Convierte n en n�mero real

                mul.d $f8, $f8, $f6     # Calcula 2.0*n
                add.d $f8, $f8, $f4     # Calcula 2.0*n + 1.0
                div.d $f8, $f4, $f8     # Calcula 1.0/(2.0*n + 1.0)  

                andi $t1, $t0, 0x0001   # Extrae bit LSB de n
                bne $t1, $zero, resta   # Salta si es impar (LSB==1)
                add.d $f0, $f0, $f8     # El t�rmino se suma
                j continua
resta:          sub.d $f0, $f0, $f8     # El t�rmino se resta
continua:       addi $t0, $t0, -1       # Decrementa n�mero de iteraciones
                bgez $t0, bucle         # Vuelve si quedan iteraciones		

                li.d $f4, 4.0           # Constante 4.0
                mul.d $f0, $f0, $f4     # Devuelve en $f0 el c�lculo de pi			                
                jr $ra
                .end
