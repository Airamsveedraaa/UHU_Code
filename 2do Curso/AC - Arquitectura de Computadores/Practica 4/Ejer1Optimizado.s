; Esto es un comentario

.data
A:        .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10  ; array de 10 enteros
Xtop:     .word 9        ; número de iteraciones
Xpointer: .word 4        ; desplazamiento entre elementos (4 bytes)
k:        .word 1        ; para el contador del bucle
c:        .word 36       ; 4*9, offset de A[9]

.text
inicio:
    ; LW R2, Xtop        R2 = 9 (contador) ya no se usa
    LW R3, Xpointer    ; R3 = 4 (desplazamiento)
    ; LW R4, k           R4 = 1 (para el bucle) ya no se usa 
    LW R5, c           ; R5 = 36, apunta a A[9]

    ; R5 apunta a A[9] (primer elemento a procesar)
    ; LW R1, A(R5)        R1 = A[9] no se usa en desenrollado

    ;iter 0 A[9]
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 1
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 2
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 3
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 4
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 5
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 6
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 7
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 8
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 9
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6,R6,R6       ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6
    ;SUB R5,R5,R3        i-- (retrocede 4 bytes) 
                       ; ultima iteracion ya hecha asi 
                       ; que no se usa mas 


    trap 6             ; fin del programa
