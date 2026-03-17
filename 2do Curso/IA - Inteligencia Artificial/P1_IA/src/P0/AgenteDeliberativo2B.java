package P0;

import java.util.Random;

class AgenteDeliberativo2B extends Agente{
	
	Random generador= new Random();
	char mem[][];
	String ultimaAccion="";

	
public AgenteDeliberativo2B(int filas, int cols) {

	mem=new char[filas][cols];
}


private int numPasos (int f,int c,int df, int dc, char mem[][], Entorno mapa) {
	 int pasos=0;
	 for(int i=1; ;i++) {
		 char casilla=mem[f+i*df][ c+i*dc];
		 if(casilla!='#'){
			 pasos++;
		 }
		 else {
			 break;
		 }
	 }
	 return pasos;
}

private void actualizarMem(int f, int c, Entorno mapa) {
	//posicion actual pisada
	mem[f][c]='.';
	
	if(f-1 >=0) {mem[f-1][c]=mapa.grid[f-1][c]==' ' ? 'v': mapa.grid[f-1][c];}
	if(f+1< mapa.filas) {mem[f+1][c]=mapa.grid[f+1][c]==' ' ? 'v':mapa.grid[f+1][c];}
	if(c-1 >=0) {mem[f][c-1]=mapa.grid[f][c-1]==' ' ? 'v': mapa.grid[f][c-1];}
	if(c+1< mapa.cols) {mem[f][c+1]=mapa.grid[f][c+1]==' ' ? 'v':mapa.grid[f][c+1];}
}


public String pensar(Entorno mapa) {
	
	int fila=mapa.agenteF;
	int col=mapa.agenteC;
	actualizarMem(fila,col,mapa);
	String acciones[]=new String[4];
	boolean posibles[]=percibir(fila,col,mapa);
	String nombres[]= {"N","S","E","O"};
	int df[]= {-1,+1,0,0};
	int dc[]= {0,0,+1,-1};
	int n=0;
	int maxPasos=-1;
	
	for(int i=0;i < 4; i++) {
		if(posibles[i] && nombres[i].equals(ultimaAccion))
		{
			ultimaAccion=nombres[i];
			return ultimaAccion;
		}
	}
	
	
	for(int i=0;i < 4 ; i++) {
	    if(posibles[i]) {
	        acciones[n]=nombres[i];
	        n++;
	    }
	}
	
	if(n==0)return "N";
	imprimirMemoria();
	String elegida=acciones[generador.nextInt(n)];
	ultimaAccion=elegida;
	return elegida;

}

public void imprimirMemoria() {
	    System.out.println("--- Estado de la memoria ---");
	    for (int i = 0; i < mem.length; i++) {
	        for (int j = 0; j < mem[i].length; j++) {
	            if (mem[i][j] == '\0') {
	                System.out.print(' '); // no visitada, espacio en blanco
	            } else {
	                System.out.print(mem[i][j]); // '.' pisada, 'v' vista
	            }
	        }
	        System.out.println(); // salto de línea por fila
	    }
	}
	
}
