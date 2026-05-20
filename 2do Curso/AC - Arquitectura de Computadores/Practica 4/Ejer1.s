; Esto es un comentario

.data
A:        .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10  ; array de 10 enteros
Xtop:     .word 9        ; número de iteraciones
Xpointer: .word 4        ; desplazamiento entre elementos (4 bytes)
k:        .word 1        ; para el contador del bucle
c:        .word 36       ; 4*9, offset de A[9]

.text
inicio:
    LW R2, Xtop        ; R2 = 9 (contador)
    LW R3, Xpointer    ; R3 = 4 (desplazamiento)
    LW R4, k           ; R4 = 1 (para el bucle)
    LW R5, c           ; R5 = 36, apunta a A[9]

    ; R5 apunta a A[9] (primer elemento a procesar)
    LW R1, A(R5)       ; R1 = A[9]

loop:
    LW R6, A(R5)       ; R6 = A[i]
    ADD R6, R6, R6     ; R6 = A[i] + A[i] = 2*A[i]
    SW A(R5), R6       ; A[i] = R6

    SUB R5, R5, R3     ; i-- (retrocede 4 bytes)
    SUB R2, R2, R4     ; contador--

    BNEZ R2, loop      ; si R2 != 0, seguir
    NOP

    trap 6             ; fin del programa