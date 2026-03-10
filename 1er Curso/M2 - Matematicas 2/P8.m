%%%PRACTICA 8, MINIMOS CUADRADOS

%%Solucion optima, aquella q pertenezca al colspace digamos
%%lsqminnorm sirve para resolver un sistema por minimos cuadrados
%%si hay varias soluciones, el comando nos devuelve la optima,que es la que
%%tiene menor norma (norm)
%%\ o left division divide los elementos uno por uno, si el sistema tiene
%%una unica solucion te la devuelve, si hay inifinitas soluciones te
%%devuelve una particular, si el sistema es incompatible, te devuelve una
%%aproximacion por minimos cuadrados (lo que nos interesa), pero no siempre
%%sera la optima, puede fallar

%%%Ejercicio 1
%sistema incompatible btw, sino no tiene gracia hacer esto :/
Coef_Mat=[1,1,0;1 1 0;1 0 1;1 0 1] %matriz d coeficientes
V_result=[1;3;8;2] %vector de resultados 
x=Coef_Mat\V_result %con la leftdivision te da una solucion
%el warning nos dice que el rango de la matriz es menor al numero de filas
%y columnas, tenemos mas incognitas que ecuaciones independientes
%comprobar distancia de la norma
N1=norm(Coef_Mat*x-V_result)
%comprobar con lsqminnorm para ver
x=lsqminnorm(Coef_Mat,V_result) 
%este si nos da la optima, demostrando que el otro ha usado una aproximacion
%usar siempre lsqminnorm, es el que fufa 
%comprobar norma
N2=norm(Coef_Mat*x-V_result)
%ambos nos dan la misma norma, porque ambos son soluciones de minimos
%cuadrados, pero solo la de lsqminnorm es la optima
N3=norm([5;-3;0])
N4=norm([2.3333;-0.3333;2.6667])
%se demuestra que la N4 es la optima xq tiene menor norma

%%%Ejercicio 2
%estamos buscando la funcion cubica y=a0+a1x+a2x^2+a3x^3 que mejor encaje
%para este set de datos, es decir, la recta que pase mas cerca de todos los
%puntos o la que pase por todos
x=[-2 -1 0 1 2 3] %datos de x
y=[-8 -1 3 1 -1 0]%datos de y
A(:,1)=ones(6,1)
A(:,2)=x'
A(:,3)=x.^2'
A(:,4)=x.^3
Sol1=A\y' %nos da la aproximacion x minimos cuadrados again
%en este caso usaremos esta, no como en la anterior que usabamos lsqminnorm
%polyfit
Sol2=polyfit(x,y,3) %nos devuelve lo mismo que el anterior, pero en orden inverso
%la primera da las respuestas desde a0 a a3, y la segunda al reves, de a3
%a a0

