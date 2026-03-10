%%%PRACTICA 9 ARITMETICA MODULAR
%%si poonemos solo gcd nos da el maximo comun divisor
%%si nombramos la salida como [d x y] nos dara la identidad de bezout, que
%%la necesitamos para las diofanticas

%todos los primos mas pequeños que el numero pasado por parametro
help primes
%ejemplo
p=primes(100)
%te da la lista de todos los numeros primos mas pequeños que 100

help lenght
%devuelve cuantos numeros hay, interesante usarlo pa saber cuantos primos
%hay antes de 100 por ejemplo
length(p) %25 primos antes del 100

help divisors
%devuelve todos los divisores no negativos del numero pasado por parametro

help factor
%devuelve un vector fila con los factores primos de n
%ejemplo
f=factor(200)
%2^3*5^2

help isprime
%como un booleano, pero el false es 0 y el true 1, el propio nombre explica
%como fufa
isprime(f)
%devuelve 1 para todos porque era una descomposicion de 200 con los primos

help nextprime
%devuelve el primer primo mas grande que n
%ejemplo
nextprime(100)
%puedes poner varios valores dentro de la llamada btw

help prevprime
%lo mismo que el anterior, pero te va a dar el anterior
%logico, mongolo, lo dice en el nombre :/

help nthprime
%devuelve el numero primo iesimo 

nthprime(235) %devuelve el numero primo numero 235 que es el 1483

help eulerPhi
%devuelve cuantos coprimos con el numero n tenemos

help mod
%devuelve el resto de la division de a entre m, el resultado de la ecuacion
%de congruencia se podria decir

help rem
%devuelve el resto de la division de a/b, LOGICAMENTE LO DICE EL NOMBRE
%COÑIO

help quorem
%lo mismo que antes pero te devuelve el cociente que satisfaga la ecuacion
%A=Q*B +R, importante que pa cada numero tiene q estar en symbolic


%%%EJERCICIO 1

A=12345678
B=12345677777778
sol=A*B

sol2=sym(A)*sym(B)
%misma solucion, pero la simbolica te da el numero completo

%%%Ejercicio 2
%todos los primos menores que 100
primes(100)
%nombramos la solucion para preguntar por la longitud y saber cuantos hay
%en total
X=primes(100)
length(X)
%25 primos mas pequeños que el 100
%nthprime(20) nos dara el primo numero 20
nthprime(20)
%cuantos primos mas pequeños que 1000000? cual el mayor?
Y=primes(1000000)
length(Y)
%hay 78948 primos antes que el 1000000 y el mayor es 999983

%%%Ejercicio 3
%buscamos el numero tal que 2^phi=1 mod(187)
%2^160=1 mod(187)
%ahora metemos quorem pa saber cuantas veces aparece el 160
eulerPhi(187) %160 como habiamos dicho
[q,r]=quorem(sym(10368),sym(160)) %64 cociente y resto 128
%por lo que la ecuacion seria 
%2^160*64+128=1 mod(187)
%que es igual a 
%2^160^64 * 2^128=1 mod(187)
mod(2^128,187)
%aqui podia haber dividido 2^128 entre 187 y llego a lo mismo
powermod(2,10368,187)
%la hijaputa dice que puede no dejarme usar esto, asi que su puta madre
powermod(3,500000,211)
%puedo usarlo para comprobar que lo que he hecho esta bien btw
%pero vaya HIJAPUTA

%%%Ejercicio 4
%nos interesa la identidad de bezout para esto
%primero comprobar que el maximo comun divisor de los numeros divide a la
%solucion
%%Apartado A
gcd(200,1768) %8 divide a 8 asi que es valido
%identidad
[d,x0,y0]=gcd(200,-1768)
%esto nos da que si multiplicamos 200*(-53) y 1768*(-6) tendremos una solucion
%concreta, aunque buscamos las genericas eso si q es cierto, y usaremos la
%ecuacion generica
syms x y t

x=x0+(-1768/8)*t
y=y0-(200/8)*t

%siendo la solucion
%x=-221t-53
%y=-25t-6
%para todo valor de T perteneciente a los eneros

%%Apartado B
[d,x0,y0]=gcd(40,50) %10 no divide a 3 asi que aqui acabamos

%%Apartado C
[d,x0,y0]=gcd(213,-1323) %3 no divide a 4 asi que paramos aqui

%%Apartado D
[d,x0,y0]=gcd(213,1123) %1 divide a 18 asi que seguimos

syms x y t

x=x0+1123*t
y=y0-213*t

%Solucion
%x=1123t+58
%y=-213t-11
%para todo T perteneciente a los enteros

%%%Ejercicio 5

%se acabaran resolviendo como las diofanticas
%teorema chino del resto
%se podra resolver si y solo si el maximo comun divisor de a y m divide a b
%%Apartado A
[d,x0,y0]=gcd(12,-236) %4 divide a 28 asi que se puede resolver
syms x t
%quiero el 28, asi que todo por 7
x=(x0*7)+(236/4)*t
%solucion
%x=59t+140

%%Apartado B
[d,x0,y0]=gcd(12,-236) %4 no divide a 30 asi que paramos aqui¿?
