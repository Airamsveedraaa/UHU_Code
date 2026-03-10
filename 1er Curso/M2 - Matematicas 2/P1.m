%%%PRACTICA 1
%%Ejercicio 1
A=[1 2 3 4; 5 6 7 8; 9 10 11 12]
%Apartado A
A(1,1)
A(1,:)
A(:,3)
A([1 3],[1 3 4]) %Poner filas y columnas a extraer entre corchetes
%Apartado B
A(1,2)=0
A(2,:)=[1 0 1 2]
A(:,4)=[]
%Apartado C, transformaciones lineales
A(2,:)=A(2,:)-A(1,:)
A(3,:)=A(3,:)-9*A(1,:)
A(3,:)=A(3,:)-8*A(2,:)
A([3 2],:)=A([2 3],:)
A(1,:)=2*A(1,:)+3*A(3,:)
%%Ejercicio 2
A=[1 2;3 4]
B=[5 6; 7 8]
%Apartado A, operaciones de ejemplo
Op1=A+B
Op2=2*A
Op3=A*B
Op4=A^(-1)%seria como hacer una inversa
Op5=A/B
Op6=A\B 
Op7=A.*B %termino a termino
Op8=A./B
%Op9=A\.B esta da error, no se porque
Op10=A^2
Op11=A.^2 %termino a termino
Op12=2.^A
Op13=A.^B %termino a termino
Op14=cos(A)
%Apartado B
[A B] %horizontalmente
[A;B] %verticalmente
%%Ejercicio 3
A
transpose(A)
inv(A)
det(A)
rank(A)
diag(A)
size(A)
length(A)
eye
zeros
ones
%%Ejercicio 4
%Apartado B
A=[1 2 3 4; 5 6 7 8; 9 10 11 12]
rref(A) %es hacer gauss jordan basicamente
rref(sym(A)) %da valores mas concretos, no usa aproximaciones
[L,U,P]=lu(A)
[L,U,P]=lu(sym(A))
[L,U]=lu(A)
[L,U]=lu(sym(A)) %siempre mejor usar el lup con el symbolic
%Apartado C
B=[0 2 3 4; 5 6 7 8; 9 10 11 12]
[L,U,P]=lu(B)
[L,U,P]=lu(sym(B))
[L,U]=lu(B)
[L,U]=lu(sym(B))
%%Ejercicio 5
A=[4 -2 -4; -2 10 5; -4 5 6]
chol(A)
