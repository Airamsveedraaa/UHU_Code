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
		 return "Z";
	 }
	 //escoger una accion aleatoria de todas las que tenemos
	 int indice=generador.nextInt(n);
	 // --- FIN CODIGO ALUMNO ---
	 return acciones[indice]; //”N” “S” “E” “0”
	 }
}

/*class AgenteDeliberativo {

public AgenteDeliberativo(int filas, int cols) {
memoria = new xxxxx[filas][cols];
}
public String pensar(Entorno mapa) {
;
// TAREA 2: Implementar lógica deliberativa
// 1. Mirar vecinos.
// 2. Si esTransitable -> añadir a opcionesSeguras.
// 3. Valorar opciones sobre la memoria

// --- INICIO CODIGO ALUMNO ---
// ...
// --- FIN CODIGO ALUMNO ---
// Prioridad: transitable, movimiento favorable …
}
return …//“acción más favorable”
	}
}*/

class AgenteGreedy{

public String pensar(Entorno mapa) {
	int fila=mapa.agenteF;
	int col=mapa.agenteC;
	
	String mejorAccion="";
	int menor=Integer.MAX_VALUE;
	int distancia;
	if(mapa.esTransitable(fila -1 , col)) {
		distancia=Math.abs(fila-1 - mapa.metaF) + (Math.abs(col - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			mejorAccion="N";
		}
	}
	if(mapa.esTransitable(fila +1 , col)) {
		distancia=Math.abs(fila+1 - mapa.metaF) + (Math.abs(col - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			mejorAccion="S";
		}
	}
	if(mapa.esTransitable(fila , col+1)) {
		distancia=Math.abs(fila - mapa.metaF) + (Math.abs(col+1 - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			mejorAccion="E";
		}
	}
	if(mapa.esTransitable(fila , col-1)) {
		distancia=Math.abs(fila - mapa.metaF) + (Math.abs(col-1 - mapa.metaC));
		if(distancia < menor) {
			menor=distancia;
			mejorAccion="O";
		}
	}
	return mejorAccion;
	}
}