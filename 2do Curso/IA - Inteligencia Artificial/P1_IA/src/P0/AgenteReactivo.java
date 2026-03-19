package P0;


class AgenteReactivo extends Agente{
	
	 
	 public String pensar(Entorno mapa) {
	 int fila=mapa.agenteF;
	 int col=mapa.agenteC;
	 int n=0;
	 String accion[]=new String[4];
	 String[] nombres= {"N","S","E","O"};
	 boolean posibles[]=percibir(fila, col, mapa);
	 
	 
	 for(int i=0;i<4;i++) {
		 if (posibles[i]) { accion[n]=nombres[i];n++;}
	 }
	 
	if(n==0) return "N";
	return accion[generador.nextInt(n)];
	 
	 }
}