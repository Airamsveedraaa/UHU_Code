package P2;
import java.util.LinkedList;
import java.util.List;


public class BusquedaAnchura {
		 private List<Nodo> Abiertos=new LinkedList<>();
		 private List<Nodo> Cerrados=new LinkedList<>();
		 
		 private List<Nodo> getSucesores(Nodo Actual, Entorno mapa){
				
			 List<Nodo> sucesores=new LinkedList();
			 int f=Actual.f;
			 int c=Actual.c;
			 int g=Actual.g+1;
			 
			 if(mapa.esTransitable(f -1, c)) {sucesores.add(new Nodo(f-1,c,Actual,"N",g+2,0));}
			 if(mapa.esTransitable(f +1, c)) {sucesores.add(new Nodo(f+1,c,Actual,"S",g+1,0));}
			 if(mapa.esTransitable(f, c+1)) {sucesores.add(new Nodo(f,c+1,Actual,"E",g+1,0));}
			 if(mapa.esTransitable(f, c-1)) {sucesores.add(new Nodo(f,c-1,Actual,"O",g+2,0));}
			 return sucesores;
		 }
		 
		 private List<Nodo> quitarRepetidos(List<Nodo> sucesores, List<Nodo> Cerrados){
			
			 List<Nodo> noRepetidos=new LinkedList();
			 for(int i=0; i<sucesores.size(); i++) {
				 Nodo s=sucesores.get(i);
			 if(!Cerrados.contains(s)) {
				 noRepetidos.add(s);
			 }
			 }
			 return noRepetidos;
		 }
		 
	 public List<String> resolver(Entorno mapa) {

		 List<Nodo> sucesores=new LinkedList();
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,0);
		 Abiertos.add(inicial);
		 int paso=1;
		 while(Abiertos.size()>0) {
			 Nodo Actual=Abiertos.removeFirst();
			 Cerrados.add(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 return reconstruirCamino(Actual);
			 }
			 else {
				 	sucesores=getSucesores(Actual,mapa);
				 	sucesores=quitarRepetidos(sucesores,Cerrados);
				 	Abiertos.addAll(sucesores);
					
				}
				System.out.println("Generados hijos: (" + sucesores + ")");
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				paso++;
		 }
	 return null;
	 }
	 private List<String> reconstruirCamino(Nodo meta) {
	 LinkedList<String> camino = new LinkedList<>();
	 Nodo actual = meta;

		System.out.println("--- ESTADÍSTICAS FINALES ---");
		System.out.println("Solución encontrada usando BFS");
		System.out.println("Camino recorrido (x,y): " + Abiertos);
	 while (actual.padre != null) {
	 camino.addFirst(actual.accion);
	 actual = actual.padre;
	 }
	 System.out.println("Coste total: " + meta.g);
	 return camino;
	 }
	}


