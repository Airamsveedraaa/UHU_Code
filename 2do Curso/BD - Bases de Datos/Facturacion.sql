set serveroutput on;

create or replace function facturacion(tf telefono.numero%TYPE,anio integer) return float is

filatelefono integer;
llamadas_anio integer;
coste float :=0;
no_ha_llamado_existe exception;
facturacion_menor_1 exception;

begin

--CUENTO TODOS Y SI ES 0 NO EXISTE EL TLF
select count(*)
into filatelefono
from telefono 
where tf=telefono.numero;


if filatelefono =0 then
raise no_ha_llamado_existe;
end if;

---CUENTO LAS LLAMADAS DE ESE AÑO, SI ES 0, RAISE
select count(*)
into llamadas_anio
from llamada 
where tf=llamada.tf_origen and extract(year from llamada.fecha_hora)=anio;

--SI NO HA HECHO LLAMADAS EN ESE AÑO SE TIRA EXCEPCION TAMBIEN
if llamadas_anio=0 then
raise no_ha_llamado_existe;
end if;


select round(sum(tarifa.coste*llamada.duracion/60),2)
into coste
from llamada inner join telefono on telefono.numero=llamada.tf_origen
inner join tarifa on tarifa.tarifa=telefono.tarifa and tarifa.compañia=telefono.compañia
where tf=telefono.numero and extract(year from llamada.fecha_hora)=anio;

--SI EL COSTE ES <1 EURO SE TIRA EXCEPCION
if coste<1 then
raise facturacion_menor_1;
end if;

return coste;

exception
when no_ha_llamado_existe then
dbms_output.put_line('El telefono no existe o no ha realizado llamadas este año');
return -1;

when facturacion_menor_1 then
dbms_output.put_line('La facturacion del telefono es menor a 1€');
return -2;

when others then
dbms_output.put_line('Error inesperado');
return -999;
end facturacion;