%%%PRACTICA 4, MAPAS LINEALES
%%Ejercicio 1
%Apartado A, nos piden hallar la matriz con respecto a la base
%literalmente, resolver las ecuaciones con respecto a la imagen y fuera
syms x y z w
f(x,y,z,w)=[2*x+z+4*w,y -3*z+2*w,-y+3*z-2*w]
f_1=subs(f,[x,y,z,w],[1,0,0,0])
f_2=subs(f,[x,y,z,w],[0,1,0,0])
f_3=subs(f,[x, y ,z, w],[0,0,1,0])
f_4=subs(f,[x, y ,z , w ],[0,0,0,1]) %con todo esto hallamos los vectores que construiran la matriz
%Apartado B, multiplicar la matriz por el vector dado, nada mas
A=[f_1' f_2' f_3' f_4']
v=[1 0 1 -1]'
A*v
%Apartado C
%hallamos el kernell ahora con respecto a la base
ker=null(A)
%Apartado D
%ECUACION DE AYUDA: dim(V)=dim(Ker(f))+dim(Img(f)), en nuestro caso V tiene
%dimension 4, como el kerr tiene dimension 1, la imagen debe tener
%dimension 3,que lo hallamosw con el colspace
colspace(A)
%Apartado E
%hallar la matriz f(U) con respecto al subespacio vectorial dado
u_1=[1,-1,0,0]'
u_2=[1,3,0,-1]' %hemos escrito los vectores que definen el subespacio U, por lo que f(U) estara compuesto por la imagen de ambos vectores

