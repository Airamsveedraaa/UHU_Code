package P0;

public abstract class Agente {
			public abstract String pensar(Entorno mapa);
			static boolean[] percibir(int f, int c, Entorno mapa) {
				boolean acciones[]=new boolean[4];
				if(mapa.esTransitable(f-1, c)) {acciones[0]=true;}
				if(mapa.esTransitable(f+1, c)) {acciones[1]=true;}
				if(mapa.esTransitable(f, c+1)) {acciones[2]=true;}
				if(mapa.esTransitable(f, c-1)) {acciones[3]=true;}
				return acciones;
			}
}
