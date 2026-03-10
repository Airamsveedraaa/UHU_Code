//S3.1

SELECT TO_CHAR(LL.fecha_hora, 'DD-MM-YYYY') as fecha
FROM mf.LLAMADA LL
WHERE LL.duracion >= 
ALL (SELECT duracion
     FROM mf.LLAMADA);


//S3.2

SELECT Cli.nombre as nombre
FROM mf.TELEFONO TLF INNER JOIN mf.CLIENTE CLI ON TLF.cliente=CLI.dni
INNER JOIN mf.COMPAÑIA CP ON TLF.compañia=CP.cif
WHERE CP.nombre LIKE 'Aotra' AND TLF.tarifa = 
(SELECT tarifa
 FROM mf.TELEFONO
 WHERE numero=654123321);
    


//S3.3

SELECT DISTINCT LL.tf_origen as origen,TLF.f_contrato as fecha,TLF.tipo as tipo
FROM mf.LLAMADA LL INNER JOIN mf.TELEFONO TLF ON LL.tf_origen=TLF.numero 
WHERE EXTRACT(month from LL.fecha_hora)=10 AND
EXTRACT (year from LL.fecha_hora)=2006 AND
LL.tf_destino =ANY
(SELECT TELEFONO.numero
FROM mf.CLIENTE INNER JOIN mf.TELEFONO ON CLIENTE.dni=TELEFONO.cliente
WHERE CLIENTE.provincia <> 'La Coruña');


//S3.4

SELECT CLI.nombre
FROM mf.CLIENTE CLI
WHERE CLI.dni IN
(SELECT TELEFONO.cliente
FROM mf.TELEFONO
WHERE TELEFONO.tarifa='dúo')
AND CLI.dni NOT IN
(SELECT TELEFONO.cliente
FROM mf.TELEFONO
WHERE TELEFONO.tarifa='autónomos');


//S3.5

SELECT CLI.nombre as nombre, TLF.numero as numero
FROM mf.CLIENTE CLI INNER JOIN mf.TELEFONO TLF ON TLF.cliente=CLI.dni 
WHERE TLF.numero IN
(SELECT LLAMADA.tf_origen
FROM mf.TELEFONO INNER JOIN mf.LLAMADA ON TELEFONO.numero=LLAMADA.tf_destino
INNER JOIN mf.COMPAÑIA ON TELEFONO.compañia=COMPAÑIA.cif
WHERE COMPAÑIA.nombre LIKE 'Petafón')
AND TLF.numero NOT IN
(SELECT LLAMADA.tf_origen
FROM mf.TELEFONO INNER JOIN mf.LLAMADA ON TELEFONO.numero=LLAMADA.tf_destino
INNER JOIN mf.COMPAÑIA ON TELEFONO.compañia=COMPAÑIA.cif
WHERE COMPAÑIA.nombre LIKE 'Aotra');



//S3.6


SELECT CLI.nombre
FROM mf.CLIENTE CLI INNER JOIN mf.TELEFONO TLF ON TLF.cliente=CLI.dni
INNER JOIN mf.LLAMADA LL ON LL.tf_origen=TLF.numero
INNER JOIN mf.COMPAÑIA CP ON TLF.compañia=CP.cif
WHERE CP.nombre LIKE 'Kietostar'
AND EXTRACT(MONTH FROM LL.fecha_hora) = 09
AND EXTRACT(YEAR FROM LL.fecha_hora) = 2006
AND LL.duracion >= ALL 
(SELECT LLAMADA.duracion
FROM mf.LLAMADA INNER JOIN mf.TELEFONO ON TELEFONO.numero=LLAMADA.tf_origen
INNER JOIN mf.COMPAÑIA ON TELEFONO.compañia=COMPAÑIA.cif
WHERE COMPAÑIA.nombre LIKE 'Kietostar'
AND EXTRACT(MONTH FROM LLAMADA.fecha_hora) = 9
AND EXTRACT(YEAR FROM LLAMADA.fecha_hora) = 2006);


//S3.7

SELECT CLI.nombre as nombre
FROM mf.TELEFONO TLF INNER JOIN mf.CLIENTE CLI ON CLI.dni=TLF.cliente
WHERE CLI.nombre <> 'Ramón Martínez Sabina' AND TLF.f_contrato < ANY
(SELECT TELEFONO.f_contrato
FROM mf.TELEFONO INNER JOIN mf.CLIENTE ON CLIENTE.dni=TELEFONO.cliente
WHERE CLIENTE.nombre = 'Ramón Martínez Sabina');