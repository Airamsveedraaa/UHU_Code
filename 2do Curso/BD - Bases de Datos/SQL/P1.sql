CREATE TABLE COMPA�IA(
cif char(9),
nombre varchar2(20),
web varchar2(30),
CONSTRAINT clave_cmpany PRIMARY KEY(cif)
);

CREATE TABLE TARIFA(
tarifa varchar2(10),
compa�ia char(9),
descripcion varchar2(50),
coste number(3,2),
CONSTRAINT clave_trifa PRIMARY KEY (tarifa,compa�ia),
CONSTRAINT ajena_trifa FOREIGN KEY (compa�ia) REFERENCES COMPA�IA (cif)
);

CREATE TABLE CLIENTE(
dni char(9),
nombre varchar2(50),
f_nac date,
direccion varchar2(100),
cp char(6),
ciudad varchar2(50),
provincia varchar2(50),
CONSTRAINT clave_cli PRIMARY KEY(dni)
);

CREATE TABLE TELEFONO(
numero char(9),
f_contrato date,
tipo char(1),
puntos number(6,0),
compa�ia char(9),
tarifa varchar2(10),
cliente char(9),
CONSTRAINT clave_tlf PRIMARY KEY (numero),
CONSTRAINT ajena_tlf_1 FOREIGN KEY (tarifa,compa�ia) REFERENCES TARIFA (tarifa,compa�ia),
CONSTRAINT ajena_tlf_2 FOREIGN KEY (compa�ia) REFERENCES COMPA�IA (cif),
CONSTRAINT ajena_tlf_3 FOREIGN KEY (cliente) REFERENCES CLIENTE (dni),
CONSTRAINT tipo_correc CHECK (tipo IN ('T','C'))
);

CREATE  TABLE LLAMADA (
tf_origen char(9),
tf_destino char(9),
fecha_hora date,
duracion number (5,0),
CONSTRAINT clave_call PRIMARY KEY (tf_origen,fecha_hora),
CONSTRAINT ajena_call_1 FOREIGN KEY (tf_origen) REFERENCES TELEFONO,
CONSTRAINT ajena_call_2 FOREIGN KEY (tf_destino) REFERENCES TELEFONO,
CONSTRAINT call_unica UNIQUE (tf_destino,fecha_hora)
);

ALTER TABLE COMPA�IA ADD CONSTRAINT cmp_unic UNIQUE (nombre);
ALTER TABLE LLAMADA ADD CONSTRAINT tf_no_rep CHECK (tf_origen != tf_destino);
ALTER TABLE TARIFA ADD CONSTRAINT coste_varemo CHECK (coste <=1.50 AND coste>=0.05);
ALTER TABLE COMPA�IA MODIFY nombre NOT NULL;
ALTER TABLE CLIENTE MODIFY nombre NOT NULL;
ALTER TABLE TARIFA MODIFY coste NOT NULL;
ALTER TABLE TELEFONO MODIFY compa�ia NOT NULL;
ALTER TABLE TELEFONO MODIFY tarifa NOT NULL;
ALTER TABLE LLAMADA MODIFY duracion NOT NULL;

ALTER TABLE TARIFA DROP CONSTRAINT ajena_trifa;
ALTER TABLE TARIFA ADD CONSTRAINT ajena_trifa FOREIGN KEY (compa�ia) REFERENCES COMPA�IA (cif) ON DELETE CASCADE;

//PARTE 2 DE LA PRACTICA
INSERT INTO COMPA�IA
VALUES('A00000001','Kietostar','https://www.kietostar.com');

INSERT INTO COMPA�IA
VALUES('B00000002','Aotra','https://www.aotra.com');

INSERT INTO TARIFA
VALUES('joven','A00000001','menores de 25 a�os',0.25);

INSERT INTO TARIFA
VALUES('d�o','A00000001','la pareja tambi�n est� en la compa��a',0.20);

INSERT INTO TARIFA
VALUES('familiar','A00000001','5 miembros de la familia en al compa��a',0.15);

INSERT INTO TARIFA
VALUES('aut�nomos','B00000002','trabajador aut�nomo',0.12);

INSERT INTO TARIFA
VALUES('d�o','B00000002','la pareja tambi�n est� en la compa��a',0.15);

UPDATE TARIFA
SET descripcion='4 miembros de la familia en la compa��a'
WHERE tarifa='familiar';

INSERT INTO COMPA�IA
VALUES('A00000001','Petafon','https://petaf�n.com');
//da error de restriccion de clave unica violada

INSERT INTO COMPA�IA
VALUES('C00000003','Aotra','https://aot.com');
//lo mismo

INSERT INTO TARIFA
VALUES('joven','D00000004','menores de 21 a�os',0.20);
//restriccion de integridad violada, entiendo que es porque no hay compa�ia con ese cif para referenciar

INSERT INTO TARIFA
VALUES('d�o','B00000002','la pareja tambi�n est� en la compa��a',0.18);
//restriccion violada de clave primaria

INSERT INTO TARIFA
VALUES('amigos','B00000002','10 amigos est�n tambi�n en la compa��a',0.15);
//deja porque varias tuplas pueden hacer referencia al mismo cif

DELETE FROM COMPA�IA
WHERE cif='B00000002';

DELETE FROM COMPA�IA
WHERE cif='C00000003';
