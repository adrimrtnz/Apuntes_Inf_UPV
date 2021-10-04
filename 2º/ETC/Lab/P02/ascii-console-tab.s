        .globl __start
        .text 0x00400000

__start:
        li $s0,32               # empieza en el caracter espacio
        li $s1,127              # termina con 126 -> '~' char
        li $s2, 4
loop:
        addi $s2,$s2,-1
        li $v0,1                # print_int
        move $a0,$s0
        syscall
        li $v0,11               # print_char
        li $a0,9                # horizontal_tab (\t) code
        syscall
        li $v0,11               # print_char
        move $a0,$s0        
        syscall                 # prints ASCII char
        
        beqz $s2, new_line      # if $s2==0 -> print('\n')
        li $v0,11               # print_char
        li $a0,9                # horizontal_tab (\t) code
        syscall
        
continue:
        addi $s0,$s0,1
        blt $s0,$s1,loop

        li $v0,10               # exit
        syscall

new_line:
        li $s2, 4
        li $v0,11               # print_char
        li $a0,10               # new_line (\n) code
        syscall
        b continue