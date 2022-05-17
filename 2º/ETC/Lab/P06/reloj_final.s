                ##########################################################
                # Segmento de datos
                ##########################################################

                .data 0x10000000
reloj:          .word 0              # HH:MM:SS (3 bytes de menor peso)

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

__start:        la $a0, reloj
                li $a1, 0x00150f2d
                jal inicializa_reloj

                la $a0, reloj
                jal imprime_reloj

                la $a0, reloj
                jal pasa_hora
                jal pasa_hora
                jal pasa_hora

                la $a0, reloj
                li $t4, 0

ini_repe:       beq $t4, 40, fin_repe 
                jal pasa_segundo            # subimos 40 segundo
                addi, $t4, $t4, 1
                j ini_repe
fin_repe:

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
                # Subrutina que incrementa el reloj en un segundo
                # Entrada: $a0 con la direccion del reloj
                # Salida: reloj incrementado en memoria
                # Nota: 23:MM:SS -> 00:MM:SS
                ########################################################## 
                
pasa_segundo:   lbu $t0, 0($a0)         # $t0 = SS
                addiu $t0, $t0, 1       # $t0 = SS++
                li $t1, 60
                beq $t0, $t1, S60       # Si SS==60 se pone SS a cero
                sb $t0, 0($a0)          # Escribe SS++
                j fin_pasa_seg
S60:            sb $zero, 0($a0)        # Escribe SS a 0 e incrementa MM
                j pasa_minuto
fin_pasa_seg:   jr $ra

                ########################################################## 
                # Subrutina que incrementa el reloj en un minuto
                # Entrada: $a0 con la direccion del reloj
                # Salida: reloj incrementado en memoria
                # Nota: 23:MM:SS -> 00:MM:SS
                ########################################################## 
                
pasa_minuto:    lbu $t0, 1($a0)         # $t0 = MM
                addiu $t0, $t0, 1       # $t0 = MM++
                li $t1, 60
                beq $t0, $t1, M60       # Si MM==60 se pone MM a cero
                sb $t0, 1($a0)          # Escribe MM++
                j fin_pasa_min
M60:            sb $zero, 1($a0)        # Escribe MM a 0 e incrementa HH
                j pasa_hora
fin_pasa_min:   jr $ra

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


                ########################################################## 
                # Subrutina que multiplica por 36 
                # Entrada:$a0
                # Salida: $v0
                # Nota: 36 = 100100 (binario) = 2^5+2^2
                ########################################################## 

mult_36:        sll $v0, $a0, 5
                sll $t0, $a0, 2
                addu $v0, $v0, $t0
                jr $ra

                ########################################################## 
                # Subrutina devuelve_reloj_en_s con desplazamientos
                # Entrada:$a0
                # Salida: $v0
                # Nota: 3600 = 2^11 + 2^10 + 2^9 + 2^4
                #         60 = 2^5 + 2^4 + 2^3 + 2^2
                ########################################################## 

devuelve_reloj_en_es_sd:
                lb $t0, 0($a0)      # Carga el byte de los segundos
                add $v0, $t0, $zero # Suma segundos a $v0
                lb $t0, 1($a0)      # Carga el byte de los minutos
                sll $t1, $t0, 5
                sll $t2, $t0, 4
                addu $v0, $t1, $t2
                sll $t1, $t0, 3
                sll $t2, $t0, 2
                addu $v0, $t1, $t2
                lb $t0, 2($a0)      # Carga el byte de las horas
                sll $t1, $t0, 11
                sll $t2, $t0, 10
                addu $v0, $t1, $t2
                sll $t1, $t0, 9
                sll $t2, $t0, 4
                addu $v0, $t1, $t2
                jr $ra

                ########################################################## 
                # Subrutina devuelve_reloj_en_s con suma, resta y desplaz
                # Entrada:$a0
                # Salida: $v0
                # Nota: 3600 = 2^11 + 2^10 + 2^9 + 2^4
                #         60 = 2^6 - 2^2 (Booth)
                ########################################################## 

devuelve_reloj_en_es_srd:
                lb $t0, 0($a0)      # Carga el byte de los segundos
                add $v0, $t0, $zero # Suma segundos a $v0
                lb $t0, 1($a0)      # Carga el byte de los minutos
                sll $t1, $t0, 6
                sll $t2, $t0, 2
                subu $t1, $t1, $t2
                addu $v0, $v0, $t1
                lb $t0, 2($a0)      # Carga el byte de las horas
                sll $t1, $t0, 11
                sll $t2, $t0, 10
                addu $v0, $t1, $t2
                sll $t1, $t0, 9
                sll $t2, $t0, 4
                addu $v0, $t1, $t2
                jr $ra

                ########################################################## 
                # Subrutina Multiplica por 31 en Booth
                # Entrada:$a0
                # Salida: $v0
                # 31 = 2^5 - 2^0
                ########################################################## 
mult_31_booth:  sll $v0, $a0, 5
                subu $v0, $v0, $a0
                jr $ra