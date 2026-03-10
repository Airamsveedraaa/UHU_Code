.model small

.code
    org 100h

  Programa_Int:
    jmp Reside
    ;;;;; Declaracion de variables
    contador db 0
    cronometro db 0, 0

  Rutina_Servicio proc
    CLI
    ; Salvar el contenido de los registros implicados en la rutina
    push ax
    push bx
    ;push ds
    push es
    push di
    
    ;Codigo rutina
    ;mov ax, cs
    ;mov ds, ax
    
    inc contador
    
    cmp contador, 18
    jnz Mostrar
    
    mov contador, 0
    inc cronometro[1]
    
    cmp cronometro[1], 60
    jnz Mostrar
    
    mov cronometro[1], 0
    inc cronometro[0]
    
      Mostrar:                  
    mov ax, 0B800h
    mov es, ax
    
    mov di, 140
    
	xor ax, ax 				;XOR sirve para "limpiar" (pone todo a 0), ya que me daba error al ejecutar
    mov al, cronometro[0]
    mov bl, 10
    div bl                  ;AH->Resto, AL->Cociente
    
    mov bh, ah             

    mov ah, 00001111b
    add al, 48 
    mov es:[di], ax
    
    mov al, bh
    add al, 48
    mov es:[di+2], ax
    
    
    mov al, 58              ; ':'
    mov es:[di+4], ax
    
    xor ax, ax				;"limpio"
    mov al, cronometro[1]
    div bl                  ;AH->Resto, AL->Cociente
    
    mov bh, ah             

    mov ah, 00001111b
    add al, 48 
    mov es:[di+6], ax
    
    mov al, bh
    add al, 48
    mov es:[di+8], ax
    
    
    ; Recupera el valor de los registros implicados en la rutina
    pop di
    pop es
    ;pop ds
    pop bx
    pop ax
    
    STI
    IRET
  ENDP

  Reside: ;etiqueta para determinar la direccion siguiente a la 
          ;ultima de la rutina que debe quedar residente

    MOV DX, offset Rutina_Servicio
    MOV AX, 0
    MOV ES, AX
    MOV SI, 1Ch*4
    CLI
    MOV ES:[SI], DX
    MOV ES:[SI+2], CS
    STI
    MOV DX, offset Reside
    INT 27h

END Programa_Int

