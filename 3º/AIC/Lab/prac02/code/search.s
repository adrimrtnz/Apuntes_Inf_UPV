        .data
a:      .dword  9,8,0,1,0,5,3,1,2,0
tam:    .dword 10       ; Tama�o del vector
cont:   .dword 0        ; N�mero de componentes == 0

        .text
start:	dadd r1,$gp,a   ; Puntero
        ld r4,tam($gp)  ; Tama�o lista
        dadd r10,r0,r0  ; Contador de ceros
 
loop:   ld r12, 0(r1)
        bnez r12, sigue
        dadd r10, r10, #1
sigue:  dadd r1,r1, #8
        dadd r4, r4, #-1
        bnez r4, loop

        trap #0
