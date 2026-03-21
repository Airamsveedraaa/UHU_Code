.MODEL SMALL

.CODE

org 100h

Programa_Int:

    JMP Reside ;+1 de inicio
    
contador_int db 0

Rutina_Servicio PROC
    
    CLI
    INC contador_int
    CMP contador_int, 4 ;4 instrucciones *3 iteraciones=12 instrucciones
    JNE fin
    
    MOV AH,0
    INT 16h
    
    
    MOV AH,4ch
    INT 21h  
    ;4 instrucciones cuando es la ultima iteracion

fin:

    STI
    IRET ;+2 instrucciones *3 iteraciones en las que no es final=6+9=15 instrucciones 
ENDP       



Reside: 

    MOV DX,offset Rutina_Servicio
    MOV AX,0
    MOV ES,AX
    MOV SI,1ch*4
    CLI
    
    MOV ES:[SI],DX
    MOV ES:[SI+2],CS
    STI
    
    MOV DX,offset Reside
    INT 27h  
    ;+10 instrucciones dejar programa residente
    
END Programa_Int