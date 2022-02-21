          .globl __start
          .data 0x10000000

demana:   .asciiz "Escribe alguna cosa: " # 26Bytes
cadena:   .space 80
res:      .asciiz "Has escrito: "
longitud: .asciiz "La longitud es: "    

          .text 0x00400000
__start:  la $a0, demana        
          la $a1, cadena        
          li $a2, 80            
          jal InputS
          la $a0, res
          la $a1, cadena
          jal OutputS
          la $a0, longitud
          la $a1, cadena
          jal Length  
          li $v0,10
          syscall

InputS:   li $v0, 4         # print_string
          syscall
          li $v0, 8         # read_string
          move $a0, $a1
          move $a1, $a2
          syscall
          jr $ra

OutputS: li $v0, 4
         syscall
         li $v0, 4
         move $a0, $a1
         syscall
         jr $ra

Length:  li $v0, 4
         syscall
         jr $ra