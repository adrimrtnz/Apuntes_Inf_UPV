        .globl __start
        .text 0x00400000

__start:
        li $s0,32               # empieza en el caracter espacio
        li $s1,127              # termina con 126 -> '~' char
loop:
        li $v0,1                # print_int
        move $a0,$s0
        syscall
        li $v0,11               # print_char
        li $a0,9                # horizontal_tab (\t) code
        syscall
        li $v0,11               # print_char
        move $a0,$s0        
        syscall                 # prints ASCII char
        li $v0,11               # print_char
        li $a0,10               # new_line (\n) code
        syscall

        addi $s0,$s0,1
        blt $s0,$s1,loop

        li $v0,10               # exit
        syscall
