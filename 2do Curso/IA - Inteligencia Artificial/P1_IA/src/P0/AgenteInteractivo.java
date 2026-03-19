package P0;

import java.util.Scanner;

class AgenteInteractivo extends Agente{
	
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
	
	if(accion.equals("S")) {
		fila++;
		}
	
	
	if(accion.equals("E")) {
		col++;
		}
	
	
	if(accion.equals("O")) {
		col--;
	}
	
	if(!entorno.esTransitable(fila, col)) {
		System.out.println("Acción no posible de realizar ");
	}
	}while(!entorno.esTransitable(fila,col));

	return accion;
	
	}
}









