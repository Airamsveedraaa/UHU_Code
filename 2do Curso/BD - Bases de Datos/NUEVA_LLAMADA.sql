set serveroutput on;

create or replace trigger NUEVA_LLAMADA

before insert on llamada


for each row

declare 
cnt_origen NUMBER;
cnt_destino NUMBER;

begin

SELECT COUNT(*) INTO cnt_origen
from llamada
where fecha_hora = :new.fecha_hora
and (:new.tf_origen = tf_origen or :new.tf_origen=tf_destino);

if cnt_origen > 0 then
raise_application_error(-20001, 'El teléfono origen ' || :NEW.tf_origen || 
                                 ' está realizando o recibiendo una llamada a las ' || :NEW.fecha_hora);
end if;


SELECT COUNT(*) INTO cnt_destino
from llamada
where fecha_hora = :new.fecha_hora
and (:new.tf_destino = tf_origen or :new.tf_destino=tf_destino);

if cnt_origen > 0 then
raise_application_error(-20002, 'El teléfono destino ' || :NEW.tf_origen || 
                                 ' está realizando o recibiendo una llamada a las ' || :NEW.fecha_hora);
end if;

end;