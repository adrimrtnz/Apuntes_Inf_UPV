                ##########################################################
                # Segmento de datos
                ##########################################################

                .data 0x10000000
reloj:          .word 0                # HH:MM:SS (3 bytes de menor peso)

cad_asteriscos: .asciiz "\n  **************************************"
cad_horas:      .asciiz "\n   Horas: "
cad_minutos:    .asciiz " Minutos: "
cad_segundos:   .asciiz " Segundos: "
cad_reloj_en_s: .asciiz "\n   Reloj en segundos: "

                ##########################################################
                # Segmento de codigo
                ##########################################################

                .globl __start
                .text 0x00400000

__start:        #la $a0, reloj
                #li $a1, 0xAB163610
                #jal inicializa_reloj

                #la $a0, reloj
                #li $a1, 23              # Horas
                #jal inicializa_reloj_hh
                #li $a1, 13              # Minutos
                #jal inicializa_reloj_mm
                #li $a1, 89              # Segundos
                #jal inicializa_reloj_ss

                la $a0, reloj
                li $a1, 66765
                jal inicializa_reloj_en_s

                la $a0, reloj
                jal devuelve_reloj_en_s

                move $a0, $v0
                jal imprime_s

                #la $a0, reloj
                #li $a1, 23              # Horas
                #li $a2, 13              # Minutos
                #li $a3, 89              # Segundos
                #jal inicializa_reloj_alt
                
                la $a0, reloj
                jal imprime_reloj
             
salir:          li $v0, 10              # Codigo de exit (10)
                syscall                 # Ultima instruccion ejecutada
                .end


                ########################################################## 
                # Subrutina que inicializa el valor del reloj
                # Entrada: $a0 con la direccion de la variable reloj
                #  y $a1 con la direccion del valor inicial de reloj
                ########################################################## 
inicializa_reloj:
                li $t0, 0x001F3F3F
                and $a1, $a1, $t0
                sw $a1, 0($a0)
                jr $ra

inicializa_reloj_en_s:
                li $t0, 60
                div $a1, $t0
                mflo $a1        # Cociente en parte LO
                mfhi $t1        # Resto en parte HI
                sb $t1, 0($a0)
                div $a1, $t0
                mflo $a1
                mfhi $t1
                sb $t1, 1($a0)
                sb $a1, 2($a0)
                jr $ra

inicializa_reloj_alt:
                li $t0, 0x001F3F3F
                sll $a1, $a1, 16
                sll $a2, $a2, 8
                add $a1, $a1, $a2
                add $a1, $a1, $a3
                and $a1, $a1, $t0

                sw $a1, 0($a0)
                jr $ra

inicializa_reloj_hh:
                li $t0, 0x1F
                and $a1, $a1, $t0
                sb  $a1, 2($a0)
                jr $ra

inicializa_reloj_mm:
                li $t0, 0x3F
                and $a1, $a1, $t0
                sb  $a1, 1($a0)
                jr $ra

inicializa_reloj_ss:
                li $t0, 0x3F
                and $a1, $a1, $t0
                sb  $a1, 0($a0)
                jr $ra

                ########################################################## 
                # Subrutina que imprime el valor del reloj
                # Entrada: $a0 con la direccion de la variable reloj
                ########################################################## 

imprime_reloj:  move $t0, $a0
                la $a0, cad_asteriscos  # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall

                la $a0, cad_horas       # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall

                lbu $a0, 2($t0)         # Lee el campo HH
                li $v0, 1               # Codigo de print_int
                syscall

                la $a0, cad_minutos     # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall

                lbu $a0, 1($t0)         # Lee el campo MM
                li $v0, 1               # Codigo de print_int
                syscall

                la $a0, cad_segundos    # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall

                lbu $a0, 0($t0)         # Lee el campo SS
                li $v0, 1               # Codigo de print_int
                syscall

                la $a0, cad_asteriscos  # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall
                jr $ra

                ########################################################## 
                # Subrutina que imprime los segundos calculados
                # Entrada: $a0 con los segundos a imprimir
                ########################################################## 

imprime_s:      move $t0, $a0
                la $a0, cad_asteriscos  # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall


                la $a0, cad_reloj_en_s  # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall

                move $a0, $t0           # Valor entero a imprimir
                li $v0, 1               # Codigo de print_int
                syscall

                la $a0, cad_asteriscos  # Direccion de la cadena
                li $v0, 4               # Codigo de print_string
                syscall
                jr $ra

                ########################################################## 
                # Subrutina que devuelve el reloj en segundos
                # Entrada: $a0 con la direccion del reloj
                ########################################################## 
                
devuelve_reloj_en_s:
                lb $t0, 0($a0)
                addu $v0, $t0, $zero
                lb $t0, 1($a0)
                li $t1, 60
                mult $t0, $t1
                mflo $t0
                addu $v0, $v0, $t0
                lb $t0, 2($a0)
                li $t1, 3600
                mult $t0, $t1
                mflo $t0
                addu $v0, $v0, $t0
                jr $ra


                ########################################################## 
                # Subrutina que incrementa el reloj en una hora
                # Entrada: $a0 con la direccion del reloj
                # Salida: reloj incrementado en memoria
                # Nota: 23:MM:SS -> 00:MM:SS
                ########################################################## 
                
pasa_hora:      lbu $t0, 2($a0)         # $t0 = HH
                addiu $t0, $t0, 1       # $t0 = HH++
                li $t1, 24
                beq $t0, $t1, H24       # Si HH==24 se pone HH a cero
                sb $t0, 2($a0)          # Escribe HH++
                j fin_pasa_hora
H24:            sb $zero, 2($a0)        # Escribe HH a 0
fin_pasa_hora:  jr $ra
