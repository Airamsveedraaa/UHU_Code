set serveroutput on;


create or replace trigger notificacion2

after update of nombre on cliente

for each row

begin

dbms_output.put_line('El nombre del cliente con dni ' || :old.dni || ' se ha actualizado.');
dbms_output.put_line('Nombre inicial: ' || :old.nombre);
dbms_output.put_line('nuevo nombre: ' || :new.nombre); 

end;