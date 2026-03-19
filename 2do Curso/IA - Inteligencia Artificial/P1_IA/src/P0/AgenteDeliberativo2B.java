package P0;


class AgenteDeliberativo2B extends Agente{
	
	char mem[][];
	String ultimaAccion="";

	
public AgenteDeliberativo2B(int filas, int cols) {

	mem=new char[filas][cols];
}


private int numPasos (int f,int c,int df, int dc, Entorno mapa) {
	 int pasos=0;
	 for(int i=1; ;i++) {
		int nf=f+i*df;
		int nc=c+i*dc;
		if(nf < 0 || nf >= mapa.filas || nc < 0 || nc >= mapa.cols) break;
		char casilla=this.mem[nf][nc];
		if(casilla=='\0' || casilla=='.' || casilla=='#')break;
		pasos++;
	 }
	 return pasos;
}

private void actualizarMem(int f, int c, Entorno mapa) {
	//posicion actual pisada
	this.mem[f][c]='.';
	
	if(f-1 >=0) {this.mem[f-1][c]=mapa.grid[f-1][c]==' ' ? 'v': mapa.grid[f-1][c];}
	if(f+1< mapa.filas) {this.mem[f+1][c]=mapa.grid[f+1][c]==' ' ? 'v':mapa.grid[f+1][c];}
	if(c-1 >=0) {this.mem[f][c-1]=mapa.grid[f][c-1]==' ' ? 'v': mapa.grid[f][c-1];}
	if(c+1< mapa.cols) {this.mem[f][c+1]=mapa.grid[f][c+1]==' ' ? 'v':mapa.grid[f][c+1];}
	
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
	    	int pasos=numPasos(fila,col,df[i],dc[i],mapa);
	    	if(pasos>maxPasos)maxPasos=pasos;
	    }
	}
	
	for(int i=0; i < 4; i++) {
		if(posibles[i]) {
			int pasos=numPasos(fila,col,df[i],dc[i],mapa);
			if(pasos==maxPasos)
				{
				acciones[n]=nombres[i];
				n++;
				}
		}
	}
	
	if(n==0)return "N";
	imprimirMemoria();
	String elegida=acciones[this.generador.nextInt(n)];
	ultimaAccion=elegida;
	return elegida;

}

public void imprimirMemoria() {
	    System.out.println("--- Estado de la memoria ---");
	    for (int i = 0; i < this.mem.length; i++) {
	        for (int j = 0; j < this.mem[i].length; j++) {
	            if (this.mem[i][j] == '\0') {
	                System.out.print(' '); // no visitada, espacio en blanco
	            } else {
	                System.out.print(this.mem[i][j]); // '.' pisada, 'v' vista
	            }
	        }
	        System.out.println(); // salto de línea por fila
	    }
	}
	
}
