package P0;

import java.util.Random;

class AgenteGreedy extends Agente implements MetricaManhatan{

	Random generador= new Random();
	
	public int distManhatan (int f,int c, Entorno mapa) {
		int dist= Math.abs(f-mapa.metaF) + Math.abs(c-mapa.metaC);
		return dist;
	}

public String pensar(Entorno mapa) {
	int fila=mapa.agenteF;
	int col=mapa.agenteC;

	
	int menor=Integer.MAX_VALUE;
	int distancia;
	int n=0; //indice para el array
	String [] acciones= new String[4]; //acciones con menor distancia manhatan
	
	//Primera pasada para obtener la menor distancia
	if(mapa.esTransitable(fila -1 , col)) {
		distancia=distManhatan(fila-1,col,mapa);
		if(distancia < menor) {
			menor=distancia;
			
		}
	}
	if(mapa.esTransitable(fila +1 , col)) {
		distancia=distManhatan(fila+1,col,mapa);
		if(distancia < menor) {
			menor=distancia;
			
		}
	}
	if(mapa.esTransitable(fila , col+1)) {
		distancia=distManhatan(fila,col+1,mapa);
		if(distancia < menor) {
			menor=distancia;
			
		}
	}
	if(mapa.esTransitable(fila , col-1)) {
		distancia=distManhatan(fila,col-1,mapa);
		if(distancia < menor) {
			menor=distancia;
		}
	}
	
	if(mapa.esTransitable(fila -1 , col)) {
		distancia=distManhatan(fila-1,col,mapa);
		if(distancia == menor) {
			acciones[n]="N";
			n++;
			
		}
	}
	if(mapa.esTransitable(fila +1 , col)) {
		distancia=distManhatan(fila+1,col,mapa);
		if(distancia == menor) {
			acciones[n]="S";
			n++;
			
		}
	}
	if(mapa.esTransitable(fila , col+1)) {
		distancia=distManhatan(fila,col+1,mapa);
		if(distancia == menor) {
			acciones[n]="E";
			n++;
			
		}
	}
	if(mapa.esTransitable(fila , col-1)) {
		distancia=distManhatan(fila,col-1,mapa);
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
	 return acciones[indice];
	}
}