set serveroutput on;

create or replace
procedure hola(nombre varchar) is
begin
    dbms_output.put_line('Hola' || nombre);
end;

