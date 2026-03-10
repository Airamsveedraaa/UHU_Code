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

