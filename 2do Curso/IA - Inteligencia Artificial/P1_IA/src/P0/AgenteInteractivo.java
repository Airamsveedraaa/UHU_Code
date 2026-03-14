package P0;

import java.util.Random;
import java.util.Scanner;
//==========================================
//TAREA 0: AGENTE INTERACTIVO
//==========================================


//==========================================
//TAREA 0: AGENTE INTERACTIVO
//==========================================
class AgenteInteractivo{
	
	Scanner scanner = new Scanner(System.in);
	
	public String pensar(Entorno entorno) {
	String accion="";
	int fila,col;
	
	do {
	System.out.println("Introduzca la accion a realizar: ");
	 accion = scanner.nextLine();
	 fila=entorno.agenteF;
	 col=entorno.agenteC;
	if(accion.equals("N")) {
		fila--;
		}
	
	else if(accion.equals("S")) {
		fila++;
		}
	
	
	else if(accion.equals("E")) {
		col++;
		}
	
	
	else if(accion.equals("O")) {
		col--;
	}
	
	if(!entorno.esTransitable(fila, col)) {
		System.out.println("Acción no posible de realizar ");
	}
	}while(!entorno.esTransitable(fila,col));
	// codigo Alumno 
	return accion;
	
	}
}

//Agente reactivo, metodo pensar en el que obtenemos la pos del agente y las posiciones de su alrededor
//tomamos la posicion en la que estamos y miramos alrededor y solo nos guardamos las transitables
//una vez teniendo eso, se mueve aleatoriamente entre las posiciones posibles

//Agente que "sabe todo", carga laberinto en memoria completamente, hacemos matriz que represente el mundo
//y cogemos la casilla que mas cerca este de la salida, es un greedy

//Agente Deliberativo, tiene "memoria", puede ver 2 movimientos mas alla del que puede realizar, puede ver 2 hacia cualquier direccion
//si es posible por ejemplo, calcular posiciones relativas transitables en la matriz
//si una opcion lleva a S , tiene prioridad, sino movemos en base a las que lleven a mas huecos libres
//El segundo deliberativo se acuerda de las casillas ya visitadas.
//es como que va generando un mundo en su memoria a partir de lo que va visitando.
//puedo usar libreria con cola prioritaria para establecer el orden de seleccion de movimientos  


class AgenteReactivo {
	// --- INICIO CODIGO ALUMNO ---
	 int fila,col;
	 Random generador= new Random();
	 // --- FIN CODIGO ALUMNO ---
	 public String pensar(Entorno mapa) {

	 // TAREA 1: Completar lógica reactiva
	 // Usar mapa.esTransitable(...) para mirar N, S, E, O
	 // Añadir a 'opciones' las direcciones válidas

	 // --- INICIO CODIGO ALUMNO ---
	 //cogemos la posicion actual del agente
	 fila=mapa.agenteF;
	 col=mapa.agenteC;
	 
	 //comprobamos las 4 direcciones posibles
	 int n=0; //dimension array de acciones posibles
	 String[] acciones=new String[4];
	 
	 if(mapa.esTransitable(fila-1,col)) {
		acciones[n]="N";
		n++; //si N transitable añadir e incrementar n
	 }
	 if(mapa.esTransitable(fila+1, col)) {
		 acciones[n]="S";
		 n++; //igual con S
	 }
	 if(mapa.esTransitable(fila, col+1)){
		 acciones[n]="E";
		 n++;
	 }
	 if(mapa.esTransitable(fila, col-1)) {
		 acciones[n]="O";
		 n++;
	 }
	 if(n==0) {
		 return "N";
	 }
	 //escoger una accion aleatoria de todas las que tenemos
	 int indice=generador.nextInt(n);
	 // --- FIN CODIGO ALUMNO ---
	 return acciones[indice]; //”N” “S” “E” “0”
	 }
}

class AgenteDeliberativo {
	
	Random generador= new Random();
	char mem[][];
	String ultimaAccion="";

	
public AgenteDeliberativo(int filas, int cols) {

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