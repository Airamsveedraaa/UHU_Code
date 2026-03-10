%%%PRACTICA 7
%comando norm, hace la raiz cuadrada de la suma de lo q este dentro
%si pones norm([1,2]) te hara la sqrt de 1^2+2^2, asi cn todo
%si pones un infinito, te coge la raiz mas grande d todos los componentes
%dot te devuelve el producto escalar de A*B
%orth te devuelve la base orthonormal de un subespacio vectorial o matriz
%qr,te devuelve la matriz triangular si no la nombras
%si la nombras con [Q,R] te hace la descomposicion qr, siendo 
%q la orthogonal matrix, y r la upper triangular, lo q hace el comando es 
%la multiplicacion de estas matrices entre si
%eejemplo
norm([1,2,],inf) %coge el maximo valor
norm([1,2],3) %raiz cubica
norm([1,2],2)%lo mismo q la siguiente
norm([1,2])

A=[1 0 1;-1 -2 0;0 1 -1]
r=rank(A) %rango 3
q=orth(A) %da 3 vectores en forma d columnas

A=[1 0 1;0 1 0;1 0 1]
r=rank(A)%rango 2
q=orth(A)%2 vectores en formqa d columnas

A=sym([1 2 0;2 4 1; 0 0 1])
r=rank(A)%rango 2
q=orth(A)%2 columnas
pretty(q)%te lo devuelve bonito, aro, si dice pretty jajaja

clc

%%%Ejercicio 1
%Apartado A
%estamos en R5
A=sym([1;0;1;-2;3])
B=sym([0;2;2;2;-5])
%comprobar que el dot product no de 0
dot(A,B) %-17, asi que no son ortogonales
%ahora comprobar que no son vectores unitarios con norm
N1=norm(A) %se cumple que no son unitarios
N2=norm(B)

%Apartado B, hallar una matriz con orth
Q=orth([A,B])
%estas dos columnas forman una orthonormal basis para el subespacio
%vectorial U
%forma numerica ahora
A=[1;0;1;-2;3]
B=[0;2;2;2;-5]
Q=orth([A,B]) %devuele la aproximacion en vez de el numero simbolico digamos


%Apartado C, usando null
A=sym([1;0;1;-2;3])
B=sym([0;2;2;2;-5])
U=null([A,B]') %con esto tenemos los 3 vectores que forman la base ortogonal
%USAR SIEMPRE VECTORES COMO FILAS, COMO COLUMNAS SE USA PAL ORTH!

%Apartado D, proyeccion del vector respecto a base orthonormal U
A=[1;0;1;-2;3]
B=[0;2;2;2;-5]
V=[1;2;3;0;-1]
U=orth([A,B])
e1=U(:,1)
e2=U(:,2)
proj_v=((dot(V,e1)/dot(e1,e1))*e1)+((dot(V,e2)/dot(e2,e2))*e2)
%Ahora con la simbolica
A=sym([1;0;1;-2;3])
B=sym([0;2;2;2;-5])
V=sym([1;2;3;0;-1])
U=orth([A,B])
e1=U(:,1)
e2=U(:,2)
proj_v=((dot(V,e1)/dot(e1,e1))*e1)+((dot(V,e2)/dot(e2,e2))*e2)
%%%Ejercicio 2, ejercicios d moodle
%%Ejercicio 6
A=sym([-1 0 3; 2 -1 0; 2 -2 1])
B=sym([-1 0 -1 3; 2 -1 1 0; 2 -2 0 1])

[Q,R]=qr(A)
[Q,R]=qr(B)

%%Ejercicio 7
A=sym([1;2])
[Q,R]=qr(A)
sol=orth(A)
sol'*sol
r=sol'*A


B=sym([1 2 1; 0 0 1; 0 0 1])
[Q,R]=qr(B)
sol2=orth(B)
sol2'*sol2
r=sol2'*B


C=sym([1;1;2])
[Q,R]=qr(C)
sol3=orth(C)
sol3'*sol3
r=sol3'*C