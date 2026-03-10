%%%Practica 2
%%Ejercicio 1
%Apartado A
A=[1 2 -2; 2 -5 1; -1 3 0]
Ampl=[1 2 -2 3; 2 -5 1 4; -1 3 0 -1]
rref(Ampl) %las soluciones salen en la ultima columna
B=[1 -1; 4 1;3 2]
Bmpl=[1 -1 1; 4 1 1; 3 2 2]
rref(Bmpl)
C=[1 2 -3 -1; 1 2 1 5]
Cmpl=[1 2 -3 -1 4; 1 2 1 5 2]
rref(Cmpl)
%Apartado B
syms x y z t
%Primer sistema
solve(x + (2*y) - (2*z)==3, 2*x -(5*y) +z==4, -x + 3*y==-1,[x,y,z],'ReturnConditions',true)
%Segundo sistema, que es incompatible por cierto
solve(x-y==1, 4*x +y==1, 3*x +(2*y)==2,[x,y],'ReturnConditions',true)
%Tercer sistema
solve(x + (2*y) -(3*z) -t ==4, x + (2*y) +z + (5*t)==2,[x,y,z,t],'ReturnConditions',true)
%El ultimo tiene infinitas soluciones, que haciendo el rref se ven cuales
%seran las variables libres (y,t) que son las que irán al otro lado del
%igual para calcular el resto
%Apartado C
A=[1 2 -2; 2 -5 1; -1 3 0]
b=[3;4;-1]
A\b %obtenemos el mismo resultado que usando el rref
linsolve(A,b) %lo mismo
sym(A)
sym(b)
A\b 
linsolve(A,b) %no se ve diferencia aparente
C=[1 2 -3 -1; 1 2 1 5]
Cmpl=[1 2 -3 -1 4; 1 2 1 5 2]
C\Cmpl
null(Cmpl) %ni idea de que es esto la vd
%% Ex2
clc
syms x y z t u x1 x2 x3 x4 x5 m k a; % Declare all variables and parameters

%FIRST EXAMPLE
% Study the rref of the augmented matrix
Am = [1 m-2 1; 1 1 m-2; m-2 1 1]
bm = [m; -2*m+2; m-2]
Ambm= [Am bm]
rref_am = rref(Ambm)

% For m ≠ 3, there's a unique solution
solve([x+(m-2)*y+z==m, x+y+(m-2)*z==-2*m+2, (m-2)*x+y+z==m-2], [x,y,z], 'ReturnConditions',true)

% Check case when m = 3
Am3 = subs(Am, m, 3)
bm3 = subs(bm, m, 3)
%x+y+z=3, x+y+z=-4, x+y+z=1, so it is inconsistent
rref_am3 = rref([Am3 bm3])
% System is inconsistent (0=1 in last row) and rank(Am3) =! rank(Am3|bm3)

%SECOND EXAMPLE
% Study the rref of the augmented matrix
Ak = [1 1 1; 1 k k^2; 1 k^2 k; 1 1 k]
bk = [k; k; k; 0]
rref_ak = rref([Ak bk])
% System is inconsistent (0=1 in last row) and rank(Ak) =! rank(Ak|bk) for all k

%THIRD EXAMPLE
% Study the rref of the augmented matrix
Aa = [1 1 4 1 a; 1 a a 1 a; a a a^2 1 a]
ba = [a; 1; a]
rref_aa = rref([Aa ba])
%If a!=0, 1, 4 there are infinitely many solutions
% General solution for a ≠ 0,1,4
sol_c = solve([x1+x2+4*x3+x4+a*x5==a, x1+a*x2+a*x3+x4+a*x5==1, a*x1+a*x2+a^2*x3+x4+a*x5==a],...
              [x1,x2,x3,x4,x5], 'ReturnConditions', true)

% Case a = 0
sol_c0 = solve([x1+x2+4*x3+x4+0*x5==0, x1+0*x2+0*x3+x4+0*x5==1, 0*x1+0*x2+0*x3+x4+0*x5==0],...
              [x1,x2,x3,x4,x5], 'ReturnConditions', true)

% Case a = 1
sol_c1 = solve([x1+x2+4*x3+x4+1*x5==1, x1+1*x2+1*x3+x4+1*x5==1, 1*x1+1*x2+1*x3+x4+1*x5==1],...
              [x1,x2,x3,x4,x5], 'ReturnConditions', true)

% Case a = 4
sol_c4 = solve([x1+x2+4*x3+x4+4*x5==4, x1+4*x2+4*x3+x4+4*x5==1, 4*x1+4*x2+16*x3+x4+4*x5==4],...
              [x1,x2,x3,x4,x5], 'ReturnConditions', true)