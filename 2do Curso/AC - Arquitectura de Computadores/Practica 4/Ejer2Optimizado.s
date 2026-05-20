; Esto es un comentario

.data
A:        .float 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0  ; array de 10 floats
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
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 1
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 2
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 3
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 4
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 5
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 6
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 7
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 8
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    SUB R5,R5,R3       ; i-- (retrocede 4 bytes)

    ;iter 9
    LF F6, A(R5)       ; R6 = A[i]
    ADDF F6,F6,F6       ; R6 = A[i] + A[i] = 2*A[i]
    SF A(R5), F6       ; A[i] = R6
    ;SUB R5,R5,R3        i-- (retrocede 4 bytes) ultima iteracion
                       ; ya hecha asi 
                       ; que no se usa mas 


    trap 6             ; fin del programa
