package P0;

import java.util.Random;

class AgenteDeliberativo2B extends Agente implements MetricaPasos , MetricaInercia,MetricaMem{
	
	Random generador= new Random();
	char mem[][];
	String ultimaAccion="";

	
public AgenteDeliberativo2B(int filas, int cols) {

	mem=new char[filas][cols];
}


public int numPasos (int f,int c,int df, int dc, char mem[][], Entorno mapa) {
	 int pasos=0;
	 for(int i=1; ;i++) {
		 if(mapa.esTransitable(f +i*df, c +i*dc) && mem[f+i*df][c+i*dc]=='\0'){
			 pasos++;
		 }
		 else {
			 break;
		 }
	 }
	 return pasos;
}

public void actualizarMem(int f, int c, Entorno mapa) {
	//posicion actual pisada
	mem[f][c]='.';
	
	if(f-1 >=0) {mem[f-1][c]=mapa.grid[f-1][c]==' ' ? 'v': mapa.grid[f-1][c];}
	if(f+1< mapa.filas) {mem[f+1][c]=mapa.grid[f+1][c]==' ' ? 'v':mapa.grid[f+1][c];}
	if(c-1 >=0) {mem[f][c-1]=mapa.grid[f][c-1]==' ' ? 'v': mapa.grid[f][c-1];}
	if(c+1< mapa.cols) {mem[f][c+1]=mapa.grid[f][c+1]==' ' ? 'v':mapa.grid[f][c+1];}
}

public boolean puedeInercia(String ultimaAccion, int f, int c, char mem[][],Entorno mapa) {
	if(ultimaAccion.equals(""))return false;
	if(ultimaAccion.equals("N")) {return mapa.esTransitable(f-1, c) && mem[f-1][c]=='\0';}
	if(ultimaAccion.equals("S")) {return mapa.esTransitable(f+1, c) && mem[f+1][c]=='\0';}
	if(ultimaAccion.equals("E")) {return mapa.esTransitable(f, c+1) && mem[f][c+1]=='\0';}
	if(ultimaAccion.equals("O")) {return mapa.esTransitable(f, c-1) && mem[f][c-1]=='\0';}
	return false;
}

public 	boolean esNuevaZona(int f,int c,char mem[][]) {
	
	return mem[f][c]=='\0';
}
public String pensar(Entorno mapa) {
	
	int fila=mapa.agenteF;
	int col=mapa.agenteC;
	String accion="";
	mem[fila][col]='.';
	String acciones[]=new String[4];
	int n=0;
	int maxPasos=-1;
	//comprobar si puedo seguir la inercia de movimiento
	if(puedeInercia(ultimaAccion,fila,col,mem,mapa)) {
				actualizarMem(fila,col,mapa);
				return ultimaAccion;
			}	
		//2.movernos en base a pasos
		if(mapa.esTransitable(fila-1, col)) {
			int pasos=numPasos(fila,col,-1,0,mem,mapa);
			if(pasos>maxPasos) {maxPasos=pasos;}
		}
		
		if(mapa.esTransitable(fila+1, col)) {
			int pasos=numPasos(fila,col,+1,0,mem,mapa);
			if(pasos>maxPasos) {maxPasos=pasos;}
		}
		
		if(mapa.esTransitable(fila, col-1)) {
			int pasos=numPasos(fila,col,0,-1,mem,mapa);
			if(pasos>maxPasos) {maxPasos=pasos;}
		}
		
		if(mapa.esTransitable(fila, col+1)) {
			int pasos=numPasos(fila,col,0,+1,mem,mapa);
			if(pasos>maxPasos) {maxPasos=pasos;}
		}
		
		//Segunda pasada para quedarnos con las de maximos pasos unicamente y elegir entre esas si es que hay empate
		if(mapa.esTransitable(fila-1, col)) {
			int pasos=numPasos(fila,col,-1,0,mem,mapa);
			if(pasos==maxPasos) {acciones[n]="N";n++;}
		}
		
		if(mapa.esTransitable(fila+1, col)) {
			int pasos=numPasos(fila,col,+1,0,mem,mapa);
			if(pasos==maxPasos) {acciones[n]="S";n++;}
		}
		
		if(mapa.esTransitable(fila, col-1)) {
			int pasos=numPasos(fila,col,0,-1,mem,mapa);
			if(pasos==maxPasos) {acciones[n]="O";n++;}
		}
		
		if(mapa.esTransitable(fila, col+1)) {
			int pasos=numPasos(fila,col,0,+1,mem,mapa);
			if(pasos==maxPasos) {acciones[n]="E";n++;}
		}
		
		if(n==0) {
		    // tercer nivel: todas las zonas nuevas agotadas, elegir entre transitables visitadas
		    String[] visitadas = new String[4];
		    int m = 0;
		    if(mapa.esTransitable(fila-1,col)) { visitadas[m]="N"; m++; }
		    if(mapa.esTransitable(fila+1,col)) { visitadas[m]="S"; m++; }
		    if(mapa.esTransitable(fila,col+1)) { visitadas[m]="E"; m++; }
		    if(mapa.esTransitable(fila,col-1)) { visitadas[m]="O"; m++; }
		    if(m==0) return "N";
		    ultimaAccion = visitadas[generador.nextInt(m)];
		    return ultimaAccion;
		}
		
		int indice=generador.nextInt(n);
		accion=acciones[indice];
		ultimaAccion=accion;
		

	imprimirMemoria();
	return accion;//“acción más favorable”

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
