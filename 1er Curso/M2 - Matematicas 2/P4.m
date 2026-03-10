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
%e
A=sym([2 0 1 4; 0 1 -3 2; 0 -1 3 -2]) %f1, f2, f3, f4 en columnas

% Basis vectors of U
u1 = [1; -1; 0; 0];
u2 = [1; 3; 0; -1];

% Compute f(U)
f_u1 = A * u1;  % = [2; -1; 1]
f_u2 = A * u2;  % = [2; -3; 3]

% Basis for f(U)
basis_fU = colspace([f_u1, f_u2])

%f
B1 = [[1; 1; 1; 1], [1; 0; 1; 0], [0; 1; 0; 0], [1; 1; -1; -1]];
rb = rank(B1) % Check if basis is full rank (should be 4)

B2 = [[1; 2; 1], [0; 1; 3], [1; 1; 1]]; 

M_C_B1 = sym([1 1 0 1;1 0 1 1;1 1 0 -1;1 0 0 -1]);

M_C_B2 = sym([1 0 1;2 1 1;1 3 1]);    
M_B2_C = inv(M_C_B2);     % B2 to standard
M_B1_C = inv(M_C_B1);     % B1 to standard 

Mf_B2_B1 = M_B2_C * A * M_B1_C 

%% Ex 2
clc

% Given vectors in R^3 and their images in R^4
v1 = [1; 1; -1]
v2 = [0; 2; 1]
v3 = [1; 1; 0]

fv1 = [0; 1; 2; -1]
fv2 = [3; -2; 0; 1]
fv3 = [4; 1; -3; 2]

% We need to express the standard basis vectors e1, e2, e3 as linear
% combinations of v1, v2, v3

% Create a matrix with v1, v2, v3 as columns
V = [v1, v2, v3]

% Find coefficients for e1 = a*v1 + b*v2 + c*v3
e1 = [1; 0; 0]
coeff_e1 = V \ e1

% Find coefficients for e2 = a*v1 + b*v2 + c*v3
e2 = [0; 1; 0]
coeff_e2 = V \ e2

% Find coefficients for e3 = a*v1 + b*v2 + c*v3
e3 = [0; 0; 1]
coeff_e3 = V \ e3

% Compute f(e1), f(e2), f(e3) using linearity of f
fe1 = coeff_e1(1)*fv1 + coeff_e1(2)*fv2 + coeff_e1(3)*fv3
fe2 = coeff_e2(1)*fv1 + coeff_e2(2)*fv2 + coeff_e2(3)*fv3
fe3 = coeff_e3(1)*fv1 + coeff_e3(2)*fv2 + coeff_e3(3)*fv3

% Construct the standard matrix of f
A = [fe1, fe2, fe3]
A