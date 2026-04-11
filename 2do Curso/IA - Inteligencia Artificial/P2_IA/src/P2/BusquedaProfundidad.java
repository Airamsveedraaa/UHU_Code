package P2;
import java.util.Stack;

public class BusquedaProfundidad {
		 private Stack<Nodo> Abiertos=new Stack<>();
		 private Stack<Nodo> Cerrados=new Stack<>();
		 private int nAbiertos;
		 private int tamMax=-1;
		 long tIni,tFin,tiempo;
		 private Stack<Nodo> getSucesores(Nodo Actual, Entorno mapa){
				
			 Stack<Nodo> sucesores=new Stack<>();
			 int f=Actual.f;
			 int c=Actual.c;
			 int g=Actual.g;
			 
			 if(mapa.esTransitable(f -1, c)) {sucesores.push(new Nodo(f-1,c,Actual,"N",g+2,0));}
			 if(mapa.esTransitable(f +1, c)) {sucesores.push(new Nodo(f+1,c,Actual,"S",g+1,0));}
			 if(mapa.esTransitable(f, c+1)) {sucesores.push(new Nodo(f,c+1,Actual,"E",g+1,0));}
			 if(mapa.esTransitable(f, c-1)) {sucesores.push(new Nodo(f,c-1,Actual,"O",g+2,0));}
			 return sucesores;
		 }
		 
		 private Stack<Nodo> quitarRepetidos(Stack<Nodo> sucesores, Stack<Nodo> Cerrados){
			
			 Stack<Nodo> noRepetidos=new Stack();
			 for(int i=0; i<sucesores.size(); i++) {
				 Nodo s=sucesores.get(i);
			 if(!Cerrados.contains(s)) {
				 noRepetidos.push(s);
			 }
			 }
			 return noRepetidos;
		 }
		 
	 public Stack<String> resolver(Entorno mapa) {

		 Stack<Nodo> sucesores=new Stack();
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,0);
		 Abiertos.push(inicial);
		 int paso=1;
		 System.out.println("Iniciando busqueda DFS...");
		 System.out.println(" Origen: " + "(" + inicial.f + "," + inicial.c + ")  -> Meta: " + "(" + mapa.metaF + "," + mapa.metaC + ")\n\n" );
		 tIni=System.currentTimeMillis();
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > tamMax) tamMax=tam; 
			 nAbiertos++;
			 Nodo Actual=Abiertos.pop();
			 Cerrados.push(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 tFin=System.currentTimeMillis();
				 tiempo=tFin-tIni;
				 return reconstruirCamino(Actual);
			 }
			 else {
				 	sucesores=getSucesores(Actual,mapa);
				 	sucesores=quitarRepetidos(sucesores,Cerrados);
					System.out.println("Generados hijos: (" + sucesores + ")");
					int n=sucesores.size();
				 	for(int i=0; i<n;i++) {
				 		Abiertos.push(sucesores.pop());
				 	}
					
				}
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				paso++;
		 }
		 tFin=System.currentTimeMillis();
		 tiempo=tFin-tIni;
		 System.out.println("Solución no encontrada usando DFS");
		 System.out.println("Nodos Expandidos: " + nAbiertos);
		 System.out.println("Tiempo de ejecucion: " + tiempo + "ms\n");
	 return null;
	 }
	 private Stack<String> reconstruirCamino(Nodo meta) {
	 Stack<String> camino = new Stack<>();
	 Stack<String>coordenadas=new Stack<>();
	 Nodo actual = meta;
	 while (actual.padre != null) {
	 camino.add(0, actual.accion);
	 coordenadas.addFirst("(" + actual.f + "," + actual.c + ")");
	 actual = actual.padre;
	 }
	 coordenadas.addFirst("(" + actual.f + "," + actual.c + ")");
	 	System.out.println("--- ESTADÍSTICAS FINALES ---");
		System.out.println("Solución encontrada usando DFS");
		System.out.println("Camino recorrido (x,y): " + coordenadas);
		System.out.println("Nodos expandidos: " + nAbiertos);
		System.out.println("Tamaño máximo de ABIERTOS: " + tamMax);
		System.out.println("Coste total: " + meta.g);
		System.out.println("Tiempo de ejecución " + tiempo + "ms");
	 return camino;
	 }
	}


