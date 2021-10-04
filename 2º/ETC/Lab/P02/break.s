          .globl __start
          .text 0x00400000

__start:
          li $s0, 0
          li $s1, 0             # counter
loop:
          li $v0,5              # read_int
          syscall
          beq $v0, 0, exit      # si v0=0 EXIT
          addu $s0,$s0,$v0
          addi $s1, $s1, 1      # counter += 1
          li $v0,1              # print_int fun
          move $a0, $s1
          syscall               # prints counter
          li $v0, 11            # print_char fun
          li $a0, '>'
          syscall               # prints > char
          li $v0,1
          move $a0, $s0
          syscall               # prints sum
          li $v0,11             # print_char fun
          li $a0, '\n'
          syscall
          b loop

exit:     
          li $v0, 11
          li $a0, '='
          syscall               # prints '=' symbol
          li $v0, 1             
          move $a0, $s0         # prints sum
          syscall
          li $v0,11             # print_char fun
          li $a0, '\n'
          syscall
          li $v0, 11
          li $a0, 'n'
          syscall               # prints 'n' symbol
          li $v0, 11
          li $a0, '='
          syscall               # prints '=' symbol
          li $v0, 1             
          move $a0, $s1         # prints n=iterations
          syscall
          li $v0,10             # exit
          syscall
