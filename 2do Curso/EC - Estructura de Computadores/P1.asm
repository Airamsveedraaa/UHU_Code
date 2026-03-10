.model small 
.data        
cadena db 5,0,0,0,0,0,0 
peso  db 8,4,2,1        
msg1 db 'Binario natural sin signo :'
msg2 db 'Complemento a 1: '
signo db '-'
 
.code       
mov ax,seg cadena 
mov ds, ax        
 
; Configurar modo de video texto
mov al,03h
mov ah,00h
int 10h

mov dx,offset cadena 
mov ah,0ah           
int 21h              

sub cadena[2],48
sub cadena[3],48
sub cadena[4],48
sub cadena[5],48 

mov al,cadena[2]
mul peso[0]    
mov bx,ax        
mov al,cadena[3]
mul peso[1]      
add bx,ax 
mov al,cadena[4]
mul peso[2]
add bx,ax
mov al,cadena[5]
mul peso[3]
add bx,ax     

push bx   

; Limpiar pantalla
mov al,03h
mov ah,00h
int 10h

; Configurar segmento extra para memoria de video
mov ax,0B800h
mov es,ax

; Mostrar msg1
mov si,offset msg1
mov di,0           ; posición inicial en memoria de video
mov cx,26          ; longitud de msg1 (¡CORREGIDO!)
mov ah,00001111b   ; atributo: fondo negro, texto blanco

mostrar_msg1:
mov al,[si]
mov es:[di],ax
inc si
add di,2
loop mostrar_msg1

; Mostrar valor binario natural sin signo
pop bx
push bx 
mov ax,bx
mov bl,10
div bl
mov cl,ah    
add cl,48
mov ch,al    
add ch,48 

; Mostrar decenas
mov al,ch
mov ah,00001111b
mov es:[di],ax
add di,2

; Mostrar unidades
mov al,cl
mov ah,00001111b
mov es:[di],ax
add di,2

; Nueva línea (pasar a siguiente fila)
pop bx   
mov di,160         ; fila 2, columna 0

; Calcular complemento a 1
mov al,cadena[2]
cmp al,1
je es_negativo_c1
jmp mostrar_c1

es_negativo_c1:
mov ax,15
sub ax,bx
mov bx,ax

mostrar_c1:
; Mostrar msg2
mov si,offset msg2
mov cx,17          ; longitud de msg2
mov ah,00001111b

mostrar_msg2:
mov al,[si]
mov es:[di],ax
inc si
add di,2
loop mostrar_msg2

; Mostrar signo si es negativo
mov al,cadena[2]
cmp al,1
jne no_signo

mov al,'-'
mov ah,00001111b
mov es:[di],ax
add di,2

no_signo:
; Mostrar valor complemento a 1
mov ax,bx
mov bl,10
div bl
mov cl,ah
mov ch,al
add cl,48
add ch,48

; Mostrar decenas
mov al,ch
mov ah,00001111b
mov es:[di],ax
add di,2

; Mostrar unidades
mov al,cl
mov ah,00001111b
mov es:[di],ax
add di,2

; Posicionar cursor al final (DI tiene la última posición + 2)
; Calcular fila y columna desde DI
mov ax,di
mov bl,160
div bl              ; AH = resto (columna*2), AL = fila
mov dh,al           ; fila en DH
mov cl,ah
shr cl,1            ; columna = (columna*2)/2
mov dl,cl           ; columna en DL
mov bh,0            ; página 0
mov ah,02h          ; función posicionar cursor
int 10h

; Esperar tecla
mov ah,00h       
int 16h

mov ah,4ch
int 21h        
end