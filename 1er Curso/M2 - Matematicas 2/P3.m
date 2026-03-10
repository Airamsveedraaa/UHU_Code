%%SESSION 3

%from b1 to b2: from b1 to c, then from c to b2
%from b1 to c: b1 in columns
%from c to b2: inverse of b2 in columns
%multiply from c to b2 by from b1 to c
%a
M_C_B1=sym([3 4 2 ; 2 1 -1; -1 1 1 ]) %matriz que va de B1 a C

M_C_B2=sym([1 0 1 ; 1 1 1; -3 2 -1 ]) %matriz que va de B2 a C

M_B2_C=inv(M_C_B2) %con esto vamos de C a B2 que es lo que buscamos

M_B2_B1=M_B2_C*M_C_B1 %multiplicar ambas y obtenemos la buscada

M_B1_B2=inv(M_B2_B1) %asi vamos de b1 a b2 que es lo contrario, por eso la inversa

%b
v_B1=sym([1 ; -2 ; 3]) %vector respecto a b1
v_B2=M_B2_B1*v_B1 %ahora lo tenemos respecto a b2 multiplicando por la matriz que va de b1 a b2

%c
w_B2=sym([1;0;-2])
v_B1=M_B1_B2*w_B2 %lo mismo pero con un vector respecto a b1
%ahora multiplicamos por la matriz que va de b2 a b1 y tenemos el vector
%respecto a b1

%%Ejercicio 2
%apartado A
U1=sym([3,8,11,2,-11; 0,2,2,2,-5; 3,4,7,-2,-1; 2,2,4,-2,1])
U1=transpose(U1)
%ahora que tenemos la matriz, hacemos rref pa ver q vectores son l.i
rref(U1) %vemos que solamente los 2 primeros, por lo que rango 2 y usamos esos 2 solo
%por lo que
B_U1=transpose(sym([3,8,11,2,-11; 0,2,2,2,-5;])) %esta seria la base respecto a U1
%ahora a hallar las ecuaciones implicitas
%dimension 5, 5-2= 3 ecuaciones necesitamos, que las sacaremos de hacer 3
%determinantes de 3x3 con las diferentes filas y las x1-x5
%hallar las diferentes ecuaciones: 
syms x1 x2 x3 x4 x5
B_U1=transpose(sym([3,8,11,2,-11; 0,2,2,2,-5;x1,x2,x3,x4,x5]))
D1=det(B_U1([1 2 3],:)) %ecuacion 1
D2=det(B_U1([1 2 4],:)) %ecuacion 2
D3=det(B_U1([1 2 5],:)) %ecuacion 3
%Apartado B
%para comprobar este cso, sustituimos los coeficientes en las x y
%comprobamos que las ecuaciones se cumplen, si dan 0 las 3 se cumple y
%pertenece
%tambien se puede hacer escribiendolo de forma matricial
A=sym([-6,-6,6,0,0; 12,-6,0,6,0;-18,15,0,0,6])
V=sym([-3;1;0;1;1])
R=A*V
%como no da todo 0, no pertenece al subespacio U1
%hacemos lo mismo con el otro vector
V2=sym([3;2;5;-4;4])
R2=A*V2 %este si pertenece a U1 porque da todo 0
%apartado C
%para conseguir las parametricas, resolvemos las implicitas y los
%coeficientes de las parametricas son la base que buscamos
syms x y z w t z1 z2 z3 
X=solve(x-y==0,y+w==0,[x,y,z,w,t],'ReturnConditions',true)
subs([X.x X.y X.z X.w X.t],[z1,z2,z3],[1,0,0])
subs([X.x X.y X.z X.w X.t],[z1,z2,z3],[0,1,0])
subs([X.x X.y X.z X.w X.t],[z1,z2,z3],[0,0,1])
%con los vectores resultantes, tenemos la base para U2
%Apartado D, usando null
A=sym([1, -1,0,0,0;0,1,0,1,0])
null(A)
%despues de escribir las implicitas en forma de matriz y resolver asi se
%ven los valores de las parametricas, que forman la bases
%Apartado e
%construimos la matriz con las ecuaciones de ambos subespacios,las del U2
%las hemos calculado arriba y las de U1 las tenemos porque son vectores
U1_int_U2=sym([1,1,-1,0,0;2,-1,0,1,0;6,-5,0,0,-2;1,-1,0,0,0;0,1,0,1,0])
rref(U1_int_U2)
%Comprobamos que coincide con el rango de la matriz
rank(U1_int_U2)
%como coincide, obviamente va a coincidir por dios, ya sabemos cuales son
%los vectores que van a formar la base, en este caso usamos el null que nos
%lo da
null(U1_int_U2([1:4],:))
%ahora con la suma de 2 subespacios
U1_add_U2=sym([3,8,11,2,-11; 0, 2, 2, 2, -5; 0, 0, 1, 0, 0; 0, 0, 0, 0, 1;-1, -1, 0, 1, 0])
rref(U1_add_U2)
%con el rref vemos que 1 ecuacion es dependiente, se tiene que ir vaya,
%vemos que es la ultima
%%ECUACION DE AYUDA: DIM(U1)+DIM(U2)=DIM(U1 intersect U2) + (U1+U2), en
%%este caso 3+2= 1+4, si nos falta un dato podemos sustituir aqui para ver
%%que nos da lo que debe darnos
%construimos la base, ahora si coño
