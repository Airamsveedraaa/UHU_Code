%%PRACTICE 6

%Ejercicio 1,diagonalizacion

%D=M^-1*A*M (D=diagonal matrix, m=invertible matrix)
%Vi=null(A-landai*I) (vector de landa i)
%mgi=dim(Vlandai)=n - rank(A-landaI)
%D formed by eigenvalues, M formed by eigenvectors
%A is diagonalizable if mai=mgi para todo i=1,...,r.
%lo de arriba se refiere a la multiplicidad algebraica y geometrica de cada
%autovalor (eigenvalue)

A=sym([5 0 -4; 0 3 0; 2 0 -1])
B=sym([4 4 0 -2; 0 4 0 0; 0 -12 -2 6; 0 0 0 4])
%Apartado A
%charpoly para hallar el polinomio caracteristico
charpoly(A)
charpoly(B)
%devuelve los coeficientes en orden descendente
%basicamente el ultimo de la derecha es el de grado 0
%charpoly nos devuelve A-landa*I, si resolvemos la ecuacion tendremos los
%autovalores/eigenvalues

%Apartado B
%polinomio A
syms x
det(A-x*eye(3)) %devuelve lo mismo, sirve pa mas bien poco
solve(ans) %esto nos da los autovalores ya, 1 con mai=1 y 3 con mai=2
%comprobar que la multiplicidad algebraica es la misma a la geometrica,
%sino no es diagonalizable
%ahora usando el comando eig para obtener lo mismo
eig(A) %y nos devuelve lo mismo, en una sola linea
eig(B) %-2 con mai=1, 4 con mai=3

%Apartado C
mgA_1=3-rank(A-1*eye(3))
mgA_3=3-rank(A-3*eye(3)) %da lo mismo que antes, asi que es diagonalizable
mgB_2=4-rank(B-(-2)*eye(4))
mgB_4=4-rank(B-4*eye(4)) %not diagonalizable

%Apartado D
%comando null para encontrar subespacio con autovectores/eigenvectors
%eigenvectors for lambda_1
Eig1=null(A-1*eye(3)) %basis for the first eigenvalue
%eigenvector for lambda_3
Eig3=null(A-3*eye(3)) %basis for the second eigenvalue
D=[1 0 0; 0 3 0; 0 0 3] %matriz con autovalores
M=[1 0 2; 0 1 0; 1 0 1] %autovectores en forma de columnas
%checking if D=M^-1*A*M
Dia=M^-1*A*M %es veridico, da la misma mielda

%matriz B ahora

[M,D,W]=eig(B) %no es diagonalizable porque M no es cuadrada y porque la multiplicidad no concuerda

%DiaB=M^-1*B*M esto dara error ya que M no es cuadrada, y por lo tanto no
%es invertible

%%Ejercicio 2, cadenas de Markov
%xn: proportion of toxic material left on the raft after n hours
%yn: proportion of toxic material on the river after n hours
%zn: proportion of toxic material on the plant after n hours

A=[0.85 0 0; 0.05 1 0; 0.10 0 1]
%Apartado A, y3? material on the river after 3 hours?
%Un=A*Un-1
%Un=A^n*U0 <- initial state (U0)
%U0=1,0,0 (all the material on the raft, initial state)
U3=A^3*[1;0;0] %12.86% of the toxic material went to the river after 3 hours

%Apartado B, long run? cuando va a infinito basicamente
%Apartado B, largo termino, seria hacer el limite se podria decir
%segun los apuntes, entiendo que debo encontrar los autovectores de la
%matriz, y esos mismos multiplicarlos por la matriz y luego por M^-1, seria
%diagonalizar la matriz digamos y luego hacerle el limite en el infinito a
%esa matriz resultante
syms n
[M,D]=eig(A)
An=M*[1 0 0; 0 1 0; 0 0 0.85^n]*M^-1
A_inf=limit(An,n,inf) %limite de la matriz, cuando n va a infinito, eso pone

%in the long run, 33,33% of the toxic material will end up in the river