%% LAB SESSION 2
%CHAPTER 1
%methods solve linear aquations:
    % rref: sol in last column
    % \. coords = B \ v cooordenadas de vector respecto a base para subespacio
        % dimension subespacio nucleo: size(null(T),2), 2 is rank matrix
    % linsolve
    %s=solve(eqns, vars) for exact solutions
    %s=solve(eqns, vars, 'ReturnConditions', true) for parametric
    %subs(matrix, variable want to replace, value to substitute)
    %null for kernel
%parametric system solving with symbolic variables

%% Ex1
clc
syms x y z t; %for everything, vars

%we put solutions in another matrix and then put them together

%FIRST EXAMPLE
A1= sym([1 2 -2 ; 2 -5 1 ; -1 3 0])
B1=sym([3;4;-1])

%rref
AB1=[A1 B1] %concatenate vertically, augmented matrix
rref1=rref(AB1) %we have sol in last column

%solve
[x1,y1,z1]=solve([x+2*y-2*z==3, 2*x-5*y+z==4, -1*x+3*y==-1], [x,y,z])

% \
X1=A1\B1

%linsolve
linsolveX1=linsolve(A1,B1)

%SECOND EXAMPLE
A2= [1 -1 ; 4 1 ; 3 2]
B2=[1;1;2]

%rref
AB2=[A2 B2]
rref2=rref(AB2) %is inconsistent because 0=1 in last row

%solve
[x2,y2]=solve([x-y==1,4*x+y==1,3*x+2*y==2], [x,y])
%it gives empty sym that means no solution

%both give a warning because of sym, we errase sym, we get an answer but we
%know system is incompatible so it shouldt give any sol
% \
X2=A2\B2

%linsolve
linsolveX2=linsolve(A2,B2)

%THIRD EXAMPLE
A3= sym([1 2 -3 -1 ; 1 2 1 5])
B3=sym([4;2])

%rref
AB3=[A3 B3]
rref3=rref(AB3) %we have sol in last column
%is inconsistent
%using solve we get one of the infinitely many
[x3,y3, z3, t3]=solve([x+2*y-3*z-t==4, x+2*y+z+5*t==2], [x,y,z,t])

%dont use [x3,y3, z3, t3]= with 'ReturnConditions',true
%'ReturnConditions',true to get the infinitely many solutions
sol3=solve([x+2*y-3*z-t==4, x+2*y+z+5*t==2], [x,y,z,t], 'ReturnConditions',true)

% \
X3=A3\B3

%linsolve
linsolveX3=linsolve(A3,B3)

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