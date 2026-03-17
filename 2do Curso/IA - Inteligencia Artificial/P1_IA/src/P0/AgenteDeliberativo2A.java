package P0;

import java.util.Random;
public class AgenteDeliberativo2A extends Agente {
	
	 Random generador= new Random();	 
	 
	 private boolean esSalida(int f, int c, Entorno mapa) {
		 return f==mapa.metaF && c==mapa.metaC;
	 }
	 
	 private int numHuecos (int f,int c,Entorno mapa) {
			int huecos=0;
			if(mapa.esTransitable(f-1,c)) {huecos++;}
			if(mapa.esTransitable(f+1, c)) {huecos++;}
			if(mapa.esTransitable(f, c-1)) {huecos++;}
			if(mapa.esTransitable(f, c+1)) {huecos++;}
			return huecos;
		}
	public String pensar(Entorno mapa) {

		int fila=mapa.agenteF;
		int col=mapa.agenteC;
		int maxHuecos=-1;
		int n=0;
		String acciones[]=new String[4];
		String nombres[]= {"N","S","E","O"};
		int df[]= {-1,+1,0,0};
		int dc[]= {0,0,+1,-1};
		boolean posibles[]=percibir(fila,col,mapa);
		int opuestos[]= {1,0,3,2,};
		
		for(int i=0;i < 4;i++)
		{
			if(posibles[i])
			{
				if(esSalida(fila+df[i],col+dc[i],mapa))return nombres[i];
				
				boolean posibles2[]=percibir(fila+df[i],col+dc[i],mapa);
				for(int j=0;j < 4 ;j++) {
					if(j!=opuestos[i])
					{
						if(posibles2[j]) 
						{
						int nf=fila+df[i]+df[j];
						int nc=col+dc[i]+dc[j];
						if(esSalida(nf,nc,mapa))return nombres[i];
						}
					}
				}
			}
		}
		
		for(int i=0;i < 4; i++) 
		{
			if(posibles[i])
				{
					int huecos=numHuecos(fila+df[i],col+dc[i],mapa);
					if(huecos > maxHuecos)maxHuecos=huecos;
				}
		}
		
		for(int i=0; i < 4;i++)
		{
			if(posibles[i]) {
				int huecos=numHuecos(fila+df[i],col+dc[i],mapa);
				if(huecos==maxHuecos)
				{
					acciones[n]=nombres[i];
					n++;
				}
			}
		}
		
		if(n==0)return "N";
		return acciones[generador.nextInt(n)];
	}
}
