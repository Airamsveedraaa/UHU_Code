package P0;

import java.util.Random;
public class AgenteDeliberativo2A {
	
	 Random generador= new Random();
	 char [][] visor;
	 
	public String pensar(Entorno mapa) {

		String accion="";
		int fila=mapa.agenteF;
		int col=mapa.agenteC;
		int maxHuecos=-1;
		int n=0;
		String acciones[]=new String[4];
		
		actualizarVisor(mapa);
		//1. comprobar si la primera o segunda lleva a S, como lo hacemos? 
		//comparando coordenadas del movimiento con la meta
		if(mapa.esTransitable(fila-1, col)) {
			//Si el norte es transitable, compruebo las otras 3 posibles 
			//Hacer NS no tiene sentido porque vuelves al sitio del que inicias
			if(fila-1==mapa.metaF && col==mapa.metaC) {
				//me lleva a salida, la eligo
				accion="N";
				return accion;
			}
			else {
				//Norte no es salida, miramos las otras 3 posibles direcciones
				if(mapa.esTransitable(fila -2, col)) {
					//si NN es transitable, ver si lleva a salida igual que antes
					if(fila-2==mapa.metaF && col==mapa.metaC) {
						//me lleva a salida, la eligo
						accion="N";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila-1, col +1)) {
					//NE como opcion
					if (fila-1==mapa.metaF && col+1==mapa.metaC){
						accion="E";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila-1, col-1)) {
					//NO como opcion
					if(fila-1==mapa.metaF && col-1==mapa.metaC) {
						accion="O";
						return accion;
					}
				}
			}
		}
		
		//Misma logica para las otras 3 posibles
		if(mapa.esTransitable(fila+1, col)) {
			//Si el Sur es transitable, compruebo las otras 3 posibles 
			//Hacer SN no tiene sentido porque vuelves al sitio del que inicias
			if(fila+1==mapa.metaF && col==mapa.metaC) {
				//me lleva a salida, la eligo
				accion="S";
				return accion;
			}
			else {
				//Sur no es salida, miramos las otras 3 posibles direcciones
				if(mapa.esTransitable(fila+2 , col)) {
					//si SS es transitable, ver si lleva a salida igual que antes
					if(fila+2==mapa.metaF && col==mapa.metaC) {
						//me lleva a salida, la eligo
						accion="S";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila+1, col +1)) {
					//SE como opcion
					if (fila+1==mapa.metaF && col+1==mapa.metaC){
						accion="E";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila+1, col-1)) {
					//SO como opcion
					if(fila+1==mapa.metaF && col-1==mapa.metaC) {
						accion="O";
						return accion;
					}
				}
			}
		}
		
		if(mapa.esTransitable(fila, col+1)) {
			//Si el este es transitable, compruebo las otras 3 posibles 
			//Hacer EO no tiene sentido porque vuelves al sitio del que inicias
			if(fila==mapa.metaF && col+1==mapa.metaC) {
				//me lleva a salida, la eligo
				accion="E";
				return accion;
			}
			else {
				//Norte no es salida, miramos las otras 3 posibles direcciones
				if(mapa.esTransitable(fila, col+2)) {
					//si EE es transitable, ver si lleva a salida igual que antes
					if(fila==mapa.metaF && col+2==mapa.metaC) {
						//me lleva a salida, la eligo
						accion="N";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila+1, col+1)) {
					//ES como opcion
					if (fila+1==mapa.metaF && col+1==mapa.metaC){
						accion="S";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila-1, col+1)) {
					//EN como opcion
					if(fila-1==mapa.metaF && col+1==mapa.metaC) {
						accion="N";
						return accion;
					}
				}
			}
		}
		
		if(mapa.esTransitable(fila, col-1)) {
			//Si el oeste es transitable, compruebo las otras 3 posibles 
			//Hacer OE no tiene sentido porque vuelves al sitio del que inicias
			if(fila==mapa.metaF && col-1==mapa.metaC) {
				//me lleva a salida, la eligo
				accion="O";
				return accion;
			}
			else {
				//Oeste no es salida, miramos las otras 3 posibles direcciones
				if(mapa.esTransitable(fila, col-2)) {
					//si OO es transitable, ver si lleva a salida igual que antes
					if(fila==mapa.metaF && col-2==mapa.metaC) {
						//me lleva a salida, la eligo
						accion="O";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila-1, col-1)) {
					//ON como opcion
					if (fila-1==mapa.metaF && col-1==mapa.metaC){
						accion="N";
						return accion;
					}
				}
				
				if(mapa.esTransitable(fila+1, col-1)) {
					//OS como opcion
					if(fila+1==mapa.metaF && col-1==mapa.metaC) {
						accion="S";
						return accion;
					}
				}
			}
		}
		
		//2. Si por lo que sea, lo anterior no surte efecto, contar huecos y elegir
		// en caso de empate se elegira aleatoriamente
		if(mapa.esTransitable(fila-1, col)) {
			int huecos=0;
			//si es transitable, contamos huecos que hay en esa direccion
			//tendremos max 3 huecos porque no podemos retroceder
			if(mapa.esTransitable(fila-2,col)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col+1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col-1)) {
				huecos++;
			}
			if(huecos > maxHuecos) {
				maxHuecos=huecos;
			}
			
		}
		
		//Idem para el resto
		
		if(mapa.esTransitable(fila+1, col)) {
			int huecos=0;
			if(mapa.esTransitable(fila+2,col)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col+1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col-1)) {
				huecos++;
			}
			if(huecos > maxHuecos) {
				maxHuecos=huecos;
			}
			
		}
		
		if(mapa.esTransitable(fila, col+1)) {
			int huecos=0;
			if(mapa.esTransitable(fila,col+2)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col+1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col+1)) {
				huecos++;
			}
			if(huecos > maxHuecos) {
				maxHuecos=huecos;
			}
			
		}
		
		if(mapa.esTransitable(fila, col-1)) {
			int huecos=0;
			if(mapa.esTransitable(fila,col-2)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col-1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col-1)) {
				huecos++;
			}
			if(huecos > maxHuecos) {
				maxHuecos=huecos;
			}
			
		}
		
		//Segunda pasada para quedarme solo con las de maximos huecos
		if(mapa.esTransitable(fila-1, col)) {
			int huecos=0;
			if(mapa.esTransitable(fila-2,col)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col+1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col-1)) {
				huecos++;
			}
			if(huecos == maxHuecos) {
				acciones[n]="N";
				n++;
			}
			
		}
		
		//Idem para el resto
		
		if(mapa.esTransitable(fila+1, col)) {
			int huecos=0;
			if(mapa.esTransitable(fila+2,col)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col+1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col-1)) {
				huecos++;
			}
			if(huecos == maxHuecos) {
				acciones[n]="S";
				n++;
			}
			
		}
		
		if(mapa.esTransitable(fila, col+1)) {
			int huecos=0;
			if(mapa.esTransitable(fila,col+2)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col+1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col+1)) {
				huecos++;
			}
			if(huecos == maxHuecos) {
				acciones[n]="E";
				n++;
			}
			
		}
		
		if(mapa.esTransitable(fila, col-1)) {
			int huecos=0;
			if(mapa.esTransitable(fila,col-2)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila-1,col-1)) {
				huecos++;
			}
			
			if(mapa.esTransitable(fila+1,col-1)) {
				huecos++;
			}
			if(huecos == maxHuecos) {
				acciones[n]="O";
				n++;
			}
			
		}
		//caso base para salida estandar
		if(n==0) {
			return "N";
		}
		
		int indice=generador.nextInt(n);
		imprimirVisor();
		return acciones[indice];
	}
	
	
	public void actualizarVisor(Entorno mapa) {
	    if(visor == null) {
	        visor = new char[mapa.filas][mapa.cols];
	        // inicializar todo a espacio vacio, el agente no sabe nada
	        for(int i = 0; i < mapa.filas; i++)
	            for(int j = 0; j < mapa.cols; j++)
	                visor[i][j] = ' ';
	    }

	    int fila = mapa.agenteF;
	    int col  = mapa.agenteC;

	    // sincronizar A y . del grid real
	    for(int i = 0; i < mapa.filas; i++)
	        for(int j = 0; j < mapa.cols; j++)
	            if(mapa.grid[i][j] == 'A' || mapa.grid[i][j] == '.')
	                visor[i][j] = mapa.grid[i][j];

	    // para cada casilla a 2 pasos, copiar lo que hay realmente en el grid
	    // si es muro se pone #, si es espacio libre se pone T, si es S se pone S
	    int[][] dospasos = {
	        {fila-2,col}, {fila-1,col+1}, {fila-1,col-1},
	        {fila+2,col}, {fila+1,col+1}, {fila+1,col-1},
	        {fila,col+2}, {fila,col-2},
	        {fila-1,col-1}, {fila+1,col-1}
	    };

	    for(int[] pos : dospasos) {
	        int f = pos[0], c = pos[1];
	        if(f >= 0 && f < mapa.filas && c >= 0 && c < mapa.cols) {
	            char casilla = mapa.grid[f][c];
	            if(casilla == '#')       visor[f][c] = '#';
	            else if(casilla == 'S')  visor[f][c] = 'S';
	            else if(casilla == ' ')  visor[f][c] = 'T';
	        }
	    }
	}

	public void imprimirVisor() {
	    System.out.println("--- Visor 2A ---");
	    for(int i = 0; i < visor.length; i++)
	        System.out.println(new String(visor[i]));
	}
}
