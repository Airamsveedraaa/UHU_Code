set serveroutput on;

create or replace
function multiplicarpordos(f float) return float is
begin
 return f*2;
 end;