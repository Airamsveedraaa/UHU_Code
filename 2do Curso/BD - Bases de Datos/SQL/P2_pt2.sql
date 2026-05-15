//S2.1

SELECT TF.coste as coste, TF.tarifa as tarifa, CP.cif as compañía
FROM mf.TARIFA TF INNER JOIN mf.COMPAÑIA CP ON TF.compañia=CP.cif
WHERE TF.descripcion LIKE '%en la compañía';

//S2.2

SELECT CLI.nombre as nombre, TLF.numero as numero,TF.tarifa as tarifa,TF.coste as coste
FROM (mf.TELEFONO TLF INNER JOIN mf.CLIENTE CLI ON TLF.cliente=CLI.dni)
INNER JOIN mf.TARIFA TF ON TLF.tarifa=TF.tarifa AND TLF.compañia=TF.compañia 
WHERE TLF.tipo LIKE 'C' AND TF.coste < 0.20;

//S2.3

SELECT TF.tarifa as tarifa,CP.nombre as nombre,TLF.numero as numero,TLF.puntos as puntos
FROM mf.TARIFA TF INNER JOIN mf.COMPAÑIA CP ON TF.compañia=CP.cif
INNER JOIN mf.TELEFONO TLF ON TF.tarifa=TLF.tarifa AND TLF.compañia=CP.cif
WHERE EXTRACT (year from TLF.f_contrato)=2006 AND TLF.puntos > 200;

//S2.4

SELECT LL.tf_origen as origen,LL.tf_destino as destino, TLF.tipo as tipo
FROM mf.TELEFONO TLF INNER JOIN mf.LLAMADA LL ON TLF.numero=LL.tf_origen 
INNER JOIN mf.CLIENTE CLI ON TLF.cliente=CLI.dni
WHERE TO_CHAR(LL.fecha_hora, 'HH24:MI') BETWEEN '08:00' AND '10:00';

//S2.5

SELECT CLI.nombre as nombre,LL.tf_origen as origen,LL.tf_destino as destino,LL.fecha_hora as fecha
FROM mf.TELEFONO TLF INNER JOIN mf.LLAMADA LL ON TLF.numero=LL.tf_origen
INNER JOIN mf.CLIENTE CLI ON TLF.cliente=CLI.dni
INNER JOIN mf.TELEFONO TLF2 ON TLF2.numero=LL.tf_destino 
AND TLF2.compañia <> TLF.compañia
WHERE LL.duracion > 15*60;