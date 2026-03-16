package P0;

import java.util.Random;

class AgenteReactivo extends Agente{
	
	Random generador= new Random();
	 
	 public String pensar(Entorno mapa) {
	 int fila=mapa.agenteF;
	 int col=mapa.agenteC;
	 
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