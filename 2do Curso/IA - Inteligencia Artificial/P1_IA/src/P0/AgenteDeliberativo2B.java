package P0;

import java.util.Random;

class AgenteDeliberativo2B {
	
	Random generador= new Random();
	char mem[][];
	String ultimaAccion="";

	
public AgenteDeliberativo2B(int filas, int cols) {

	mem=new char[filas][cols];
}
public String pensar(Entorno mapa) {
	
	int fila=mapa.agenteF;
	int col=mapa.agenteC;
	String accion="";
	mem[fila][col]='.';
	String acciones[]=new String[4];
	String visitadas[]=new String[4];
	int n=0;
	int m=0;
	
	//comprobar si puedo seguir la inercia de movimiento
	if(!ultimaAccion.equals("")) {
		//si entra es que la ultima accion ha sido una valida
		if(ultimaAccion.equals("N")) {
			if(mapa.esTransitable(fila -1, col) && mem[fila-1][col]=='\0') {
				//si es transitable Y ADEMÁS, no ha sido visitada, la devuelvo directamente
				ultimaAccion="N";
				return ultimaAccion;
			}
		}
		if(ultimaAccion.equals("S")) {
			if(mapa.esTransitable(fila +1, col) && mem[fila+1][col]=='\0') {
				//si es transitable Y ADEMÁS, no ha sido visitada, la devuelvo directamente
				ultimaAccion="S";
				return ultimaAccion;
			}
		}
		if(ultimaAccion.equals("E")) {
			if(mapa.esTransitable(fila, col+1) && mem[fila][col+1]=='\0') {
				//si es transitable Y ADEMÁS, no ha sido visitada, la devuelvo directamente
				ultimaAccion="E";
				return ultimaAccion;
			}
		}
		if(ultimaAccion.equals("O")) {
			if(mapa.esTransitable(fila, col-1) && mem[fila][col-1]=='\0') {
				//si es transitable Y ADEMÁS, no ha sido visitada, la devuelvo directamente
				ultimaAccion="O";
				return ultimaAccion;
			}
		}
	}
	
	if(mapa.esTransitable(fila -1, col)) {
		//si Norte es transitable
		if(mem[fila-1][col]=='\0') {
			acciones[n]="N";
			n++;
			mem[fila-1][col]='v'; //vista esa casilla, si es visitada se pone un '.'
		}
		else {
			visitadas[m]="N";
			m++;
		}
	}
	if(mapa.esTransitable(fila +1, col)) {
		//si Sur es transitable
		if(mem[fila+1][col]=='\0') {
			acciones[n]="S";
			n++;
			mem[fila+1][col]='v';
		}
		else {
			visitadas[m]="S";
			m++;
		}
	}
	if(mapa.esTransitable(fila, col+1)) {
		//si Este es transitable
		if(mem[fila][col+1]=='\0') {
			acciones[n]="E";
			n++;
			mem[fila][col+1]='v';
		}
		else {
			visitadas[m]="E";
			m++;
		}
	}
	if(mapa.esTransitable(fila, col-1)) {
		//si Oeste es transitable
		if(mem[fila][col-1]=='\0') {
			acciones[n]="O";
			n++;
			mem[fila][col-1]='v';
		}
		else {
			visitadas[m]="O";
			m++;
		}
	}
	
	if(n!=0) {
		//si n es distinto de 0, tengo al menos una transitable
		//elegir entre 1 de todas esas transitables
		int indice=generador.nextInt(n);
		accion=acciones[indice];
		ultimaAccion=accion;
	}
	else if(m!=0) {
		//si es 0, es que todas han sido visitadas ya, hay que tirar del otro array
		int indice=generador.nextInt(m);
		accion=visitadas[indice];
		ultimaAccion=accion;
	}
	else {
		return "N"; //caso base para la salida estandar y no consumir ciclos
	}
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
