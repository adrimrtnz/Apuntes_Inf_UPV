          .globl __start
          .text 0x00400000

__start:
          li $s0, 0
loop:
          li $v0,5              # read_int
          syscall
          addu $s0,$s0,$v0
          li $v0,1              # print_int
          move $a0, $s0
          syscall
          li $v0,11             # print_char
          li $a0, '\n'
          syscall
          b loop
  
          li $v0,10             # exit
          syscall
