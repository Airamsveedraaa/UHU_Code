//ejemplo 
SELECT *
FROM mf.cliente
WHERE provincia='Huelva';




//S1.1

SELECT nombre 
FROM mf.compañia C
WHERE C.web LIKE '%et%' AND C.web LIKE '%com';

//S1.2

SELECT nombre,direccion
FROM mf.cliente CL
WHERE (EXTRACT(year FROM CL.f_nac)=1973 OR EXTRACT(year FROM CL.f_nac)=1985) 
      AND CL.cp LIKE '15%' ORDER BY CL.nombre ASC,CL.direccion DESC;
      
      
//S1.3

SELECT tf_destino
FROM mf.llamada LL
WHERE LL.tf_origen='666010101' 
      AND EXTRACT(year FROM LL.fecha_hora)=2006; 

//S1.4

SELECT tf_origen
FROM mf.llamada LL
WHERE LL.tf_destino='666010101' 
      AND TO_CHAR (fecha_hora,'HH24:MI') BETWEEN '10:00' AND '12:00';

//S1.5

SELECT DISTINCT tarifa
FROM mf.telefono TL
WHERE TL.cliente LIKE '%2%'
      AND TL.puntos BETWEEN 10000 AND 20000
      AND TL.tipo='C';
      
//S1.6

SELECT numero,tarifa
FROM mf.telefono TL
WHERE EXTRACT(month FROM f_contrato)=05
      AND TL.tarifa <> 'joven'
      AND TL.numero LIKE '%9'
      ORDER BY TL.puntos DESC;
      
//S1.7

SELECT tf_destino
FROM mf.llamada LL
WHERE LL.tf_origen='654345345'
      AND TO_CHAR(fecha_hora,'MM') BETWEEN '10' AND '11'
      AND LL.duracion > 250;
      
//S1.8

SELECT nombre
FROM mf.cliente CL
WHERE EXTRACT(year FROM CL.f_nac) BETWEEN 1970 AND 1985
      AND CL.provincia='Huelva' ORDER BY CL.ciudad ASC,CL.provincia DESC;

