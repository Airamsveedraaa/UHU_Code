.MODEL SMALL
.DATA
    palabra db 'Papa$',0   
    pos_pantalla dw 0
	pos_columna db 0 
	pos_fila db 0 
	contador dw 0

    
.CODE         

    ;inicializacion seg datos mediante registro
	MOV AX, seg palabra
	MOV DS, AX 
	
	MOV AL, 03h
	MOV AH, 0h
	INT 10h
                 
    ;lo mismo con seg extra
	MOV AX, 0B800h	
	MOV ES, AX 

	MOV DI, pos_pantalla  
	MOV SI,0   
	
	; 9 instrucciones ejecutadas para inicializacion
escribe:      
	
	               
	;rutina para mostrar la palabra y limpiar pantalla al acabar
	MOV AL, palabra[SI]
	MOV AH, 0Fh 
	MOV ES:[DI], AX 
	
	ADD DI, 2 
	INC SI ;paso al siguiente caracter de la palabra
	INC pos_columna
	 
	CMP palabra[SI],'$' ;he llegado a final de la paalabra? no: escribo, si: reinicio la posicion de SI
	JNE escribe   
	
	;8 instrucciones para caracteres que no son final de palabra
	
	MOV SI,0
	CMP pos_columna, 80  ;he llenado una fila de la pantalla? 
	JNZ escribe  
	;+3 instrucciones si es final de palabra ya que resetea SI a 0 para escribir desde el principio por donde iba
	
	MOV pos_columna,0
	INC pos_fila
	CMP pos_fila,25  ;he llenado una pantalla completa? 
	JNZ escribe 
	;+4 instrucciones limpiar pantalla
	
	MOV AL,03h
	MOV AH,0h
	INT 10h
	
	MOV DI,0
	MOV SI,0
	MOV pos_columna,0
	MOV pos_fila,0
	JMP escribe
	;+8 instrucciones finalizacion de programa
	
	
END  

   ;RECUENTO INSTRUCCIONES, PRUEBA: 
   ;9 instrucciones inicio programa
   ;8 por cada caracter que no es fin de palabra
   ;11 si es un caracter de fin de palabra, una palabra de 4 letras: 3*8+11=35 instrucciones
   ;4 instrucciones si llena pantalla
   ;8 fin de programa
   ;RESIDE:
   ;1 de inicio
   ;4*3+2*3 instrucciones por cada interrupcion antes de 4 interrupciones contadas ->18 instrucciones
   ;10 instrucciones dejar residente el programa que se ejecutan una sola vez
   ;en total:2 filas completas (80*2) + 20 caracteres, al ser todo palabras completas
   ; resulta en 160/4+20=60 palabras mostradas, para 4 letras son 35 instrucciones por palabra
   ; por lo que resulta en 35*60=2100+9+8+4+8+1+18+10=2158 instrucciones en total
   ;tiempo corriendo 4/18,2=0,2197secs
   ;MIPS=instrucciones/(tiempo*10^6)=0,009822MIPS 
