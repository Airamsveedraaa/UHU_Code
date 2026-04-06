package P2;
import java.util.Stack;


public class BusquedaProfundidad {
		 private Stack<Nodo> Abiertos=new Stack<>();
		 private Stack<Nodo> Cerrados=new Stack<>();
		 
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
		 while(Abiertos.size()>0) {
			 Nodo Actual=Abiertos.pop();
			 Cerrados.push(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
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
	 return null;
	 }
	 private Stack<String> reconstruirCamino(Nodo meta) {
	 Stack<String> camino = new Stack<>();
	 Nodo actual = meta;

		System.out.println("--- ESTADÍSTICAS FINALES ---");
		System.out.println("Solución encontrada usando DFS");
		System.out.println("Camino recorrido (x,y): " + Abiertos);
	 while (actual.padre != null) {
	 camino.addFirst(actual.accion);
	 actual = actual.padre;
	 }
	 System.out.println("Coste total: " + meta.g);
	 return camino;
	 }
	}


