package P0;

import java.util.Random;

class AgenteGreedy{

public String pensar(Entorno mapa) {
	int fila=mapa.agenteF;
	int col=mapa.agenteC;
	 Random generador= new Random();

	
	int menor=Integer.MAX_VALUE;
	int distancia;
	int n=0; //indice para el array
	String [] acciones= new String[4]; //acciones con menor distancia manhatan
	
	//Primera pasada para obtener la menor distancia
	if(mapa.esTransitable(fila -1 , col)) {
		distancia=Math.abs(fila-1 - mapa.metaF) + (Math.abs(col - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			
		}
	}
	if(mapa.esTransitable(fila +1 , col)) {
		distancia=Math.abs(fila+1 - mapa.metaF) + (Math.abs(col - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			
		}
	}
	if(mapa.esTransitable(fila , col+1)) {
		distancia=Math.abs(fila - mapa.metaF) + (Math.abs(col+1 - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			
		}
	}
	if(mapa.esTransitable(fila , col-1)) {
		distancia=Math.abs(fila - mapa.metaF) + (Math.abs(col-1 - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
		}
	}
	
	if(mapa.esTransitable(fila -1 , col)) {
		distancia=Math.abs(fila-1 - mapa.metaF) + (Math.abs(col - mapa.metaC));
		if(distancia == menor) {
			acciones[n]="N";
			n++;
			
		}
	}
	if(mapa.esTransitable(fila +1 , col)) {
		distancia=Math.abs(fila+1 - mapa.metaF) + (Math.abs(col - mapa.metaC));
		if(distancia == menor) {
			acciones[n]="S";
			n++;
			
		}
	}
	if(mapa.esTransitable(fila , col+1)) {
		distancia=Math.abs(fila - mapa.metaF) + (Math.abs(col+1 - mapa.metaC));
		if(distancia == menor) {
			acciones[n]="E";
			n++;
			
		}
	}
	if(mapa.esTransitable(fila , col-1)) {
		distancia=Math.abs(fila - mapa.metaF) + (Math.abs(col-1 - mapa.metaC));
		if(distancia == menor) {
			acciones[n]="O";
			n++;
		}
	}
	
	//caso en el que no haya acciones posibles
	if(n==0) {
		 return "N";
	 }
	
	//devolver uno aleatorio de los añadidos al array
	 int indice=generador.nextInt(n);
	 // --- FIN CODIGO ALUMNO ---
	 return acciones[indice]; //”N” “S” “E” “0” 
	}
}