          .globl __start
          .text 0x00400000

__start:  li $a3, 'M'
          jal Input
          li $v0,5          # read_int
          syscall
          move $a0,$v0
          li $a3, 'Q'
          jal Input
          li $v0,5          # read_int
          syscall
          move $a1,$v0

          bltz $a1, change_sign  

continue: jal Mult
          li $a3, 'R'
          move $a1,$v0
          jal Output
          li $v0,10         # exit
          syscall

Mult:     li $v0, 0
          beqz $a1, MultRet

MultFor:  add $v0, $v0, $a0
          addi $a1, $a1, -1         # Suma $a0+$a0 $a1 veces
          bne $a1, $zero, MultFor

MultRet:  jr $ra

Input:    move $a2, $a0       # para no cargarnos si hay algo cargado
          li $v0, 11          # print_char
          move $a0, $a3
          syscall
          li $v0, 11
          li $a0, '='
          syscall
          move $a0, $a2
          jr $ra

Output:   li $v0, 11
          move $a0, $a3
          syscall
          li $v0, 11
          li $a0, '='
          syscall
          li $v0, 1
          move $a0, $a1
          syscall
          li $v0, 11
          li $a0, '\n'
          syscall
          jr $ra

change_sign:
          sub $a0, $0, $a0
          sub $a1, $0, $a1
          j continue