package P0;


class AgenteGreedy extends Agente{
	
	private int distManhatan (int f,int c, Entorno mapa) {
		int dist= Math.abs(f-mapa.metaF) + Math.abs(c-mapa.metaC);
		return dist;
	}

public String pensar(Entorno mapa) {
	int fila=mapa.agenteF;
	int col=mapa.agenteC;

	
	int menor=Integer.MAX_VALUE;
	int distancia;
	int n=0; //indice para el array
	String [] accion= new String[4]; //acciones con menor distancia manhatan
	String nombres[]= {"N","S","E","O"};
	int df[]= {-1,+1,0,0};
	int dc[]= {0,0,+1,-1};
	boolean posibles[]=percibir(fila,col,mapa);
	//primera pasada, obtener mejor distancia manhatan
	for(int i=0;i<4;i++) 
	{
		if(posibles[i]) 
		{
			distancia=distManhatan(fila+df[i],col+dc[i],mapa);
			if(distancia < menor) menor=distancia;
		}
	}
	
	//Segunda pasada, quedarnos con las mejores opciones y elegir entre ellas
	for(int i=0;i<4;i++) 
	{
		if(posibles[i]) 
		{
			distancia=distManhatan(fila+df[i],col+dc[i],mapa);
			if(distancia == menor) 
			{ accion[n]=nombres[i]; 
			n++;
			}
		}
	}
	
	if(n==0)return "N";
	return accion[this.generador.nextInt(n)];
}
}