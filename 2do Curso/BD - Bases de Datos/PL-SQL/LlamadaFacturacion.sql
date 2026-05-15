set serveroutput on;

create or replace procedure LlamadaFacturacion (anio integer) is

cursor a_llamada is
select distinct telefono.numero
from telefono inner join llamada on llamada.tf_origen=telefono.numero
where extract(year from llamada.fecha_hora)=anio;

tf telefono.numero%TYPE;
coste float :=0;

begin

open a_llamada;

loop 
fetch a_llamada into tf;
exit when a_llamada%notfound;

coste :=facturacion(tf,anio);

dbms_output.put_line('Telefono:' || tf || '- facturacion:' || coste);
end loop;

close a_llamada;
end LlamadaFacturacion;