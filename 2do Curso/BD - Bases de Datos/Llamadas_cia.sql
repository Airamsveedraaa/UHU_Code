SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE llamadas_cia(cp COMPAÑIA.nombre%TYPE, fecha DATE) IS

    CURSOR llamadas IS
        SELECT 
            t.numero,
            COUNT(l.tf_origen) AS num_ll,  -- solo cuenta llamadas reales
            COUNT(CASE WHEN l.duracion > 100 THEN 1 END) AS num_100,
            ROUND(
                CASE WHEN COUNT(l.tf_origen) = 0 THEN 0
                     ELSE COUNT(CASE WHEN l.duracion > 100 THEN 1 END) * 100 / COUNT(l.tf_origen)
                END
            ) AS porcentaje
        FROM telefono t
        LEFT JOIN llamada l
               ON t.numero = l.tf_origen AND TRUNC(l.fecha_hora) = TRUNC(fecha)
        INNER JOIN compañia c
               ON t.compañia = c.cif
        WHERE c.nombre = cp
        GROUP BY t.numero;

    tf llamadas%ROWTYPE;
    num_llamadas_total INTEGER := 0;

BEGIN
    dbms_output.put_line('Llamadas realizadas por telefonos de la compañia "' || cp || '"');
    dbms_output.put_line('Telefono Num__LL Num_100 %');

    OPEN llamadas;
    LOOP
        FETCH llamadas INTO tf;
        EXIT WHEN llamadas%NOTFOUND;

        -- Acumular número total de llamadas
        num_llamadas_total := num_llamadas_total + tf.num_ll;

        -- Mostrar información
        dbms_output.put_line(tf.numero || ' ' || tf.num_ll || ' ' || tf.num_100 || ' ' || tf.porcentaje || '%');
        dbms_output.put_line('-------------------------------------------------------');
    END LOOP;

    dbms_output.put_line('Numero total de llamadas realizadas: ' || num_llamadas_total);

    CLOSE llamadas;

END llamadas_cia;
