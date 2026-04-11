package P2;
import java.util.Queue;
import java.util.PriorityQueue;
import java.util.List;
import java.util.LinkedList;


public class BusquedaAEstrella {
		 private Queue<Nodo> Abiertos=new PriorityQueue<>();
		 private Queue<Nodo> Cerrados=new PriorityQueue<>();
		 private int tamMax=-1;
		 private int nAbiertos;
		 long tIni,tFin,tiempo;
		 private Queue<Nodo> getSucesores(Nodo Actual, Entorno mapa){
				
			 Queue<Nodo> sucesores=new PriorityQueue<>();
			 int f=Actual.f;
			 int c=Actual.c;
			 int g=Actual.g;
			 
			 if(mapa.esTransitable(f -1, c)) {
				 int h=Math.abs((f-1)-mapa.metaF) + Math.abs(c-mapa.metaC); //heurística de Distancia Manhattan
				 sucesores.add(new Nodo(f-1,c,Actual,"N",g+2,h));}
			 if(mapa.esTransitable(f+1, c)) {
				 int h=Math.abs((f+1)-mapa.metaF) + Math.abs(c-mapa.metaC); //heurística de Distancia Manhattan
				 sucesores.add(new Nodo(f+1,c,Actual,"S",g+1,h));}
			 if(mapa.esTransitable(f, c+1)) {
				 int h=Math.abs(f-mapa.metaF) + Math.abs((c+1)-mapa.metaC); //heurística de Distancia Manhattan
				 sucesores.add(new Nodo(f,c+1,Actual,"E",g+1,h));}
			 if(mapa.esTransitable(f, c-1)) {
				 int h=Math.abs(f-mapa.metaF) + Math.abs((c-1)-mapa.metaC); //heurística de Distancia Manhattan
				 sucesores.add(new Nodo(f,c-1,Actual,"O",g+2,h));}
			 return sucesores;
		 }
		 
		 private Queue<Nodo> quitarRepetidos(Queue<Nodo> sucesores, Queue<Nodo> Cerrados){
			
			 Queue<Nodo> noRepetidos=new PriorityQueue<>();
			 List<Nodo> temp=new LinkedList<>(sucesores);
			 for(int i=0; i<temp.size(); i++) {
				 Nodo s=temp.get(i);
			 if(!Cerrados.contains(s)) {
				 noRepetidos.add(s);
			 }
			 }
			 return noRepetidos;
		 }
		 
	 public List<String> resolver(Entorno mapa) {

		 Queue<Nodo> sucesores=new PriorityQueue<>();
		 int Hinicial=Math.abs(mapa.agenteF-mapa.metaF) + Math.abs(mapa.agenteC - mapa.metaC);
		 tIni=System.currentTimeMillis();
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,Hinicial);
		 Abiertos.add(inicial);
		 int paso=1;
		 System.out.println("Iniciando busqueda A*...");
		 System.out.println(" Origen: " + "(" + inicial.f + "," + inicial.c + ")  -> Meta: " + "(" + mapa.metaF + "," + mapa.metaC + ")\n\n" );
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > tamMax) tamMax=tam;
			 nAbiertos++;
			 Nodo Actual=Abiertos.remove();
			 Cerrados.add(Actual);
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
				 	Abiertos.addAll(sucesores);
				 	Actual=Abiertos.peek();
				}
				System.out.println("Generados hijos: (" + sucesores + ")");
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				paso++;
		 }
		 tFin=System.currentTimeMillis();
		 tiempo=tFin-tIni;
		 System.out.println("Solución no encontrada usando A*");
		 System.out.println("Nodos Expandidos: " + nAbiertos);
		 System.out.println("Tiempo de ejecucion: " + tiempo + "ms\n");
	 return null;
	 }
	 private List<String> reconstruirCamino(Nodo meta) {
	 LinkedList<String> camino = new LinkedList<>();
	 LinkedList<String>coordenadas=new LinkedList<>();
	 Nodo actual = meta;
	 while (actual.padre != null) {
	 camino.addFirst(actual.accion);
	 coordenadas.addFirst("(" + actual.f + "," + actual.c + ")");
	 actual = actual.padre;
	 }
	 coordenadas.addFirst("(" + actual.f + "," + actual.c + ")");
	 	System.out.println("--- ESTADÍSTICAS FINALES ---");
		System.out.println("Solución encontrada usando A*");
		System.out.println("Camino recorrido (x,y): " + coordenadas);	
		System.out.println("Coste total del camino: " + meta.g);
		System.out.println("Nodos expandidos: " + nAbiertos);
		System.out.println("Tamaño máximo de ABIERTOS: " + tamMax);
		System.out.println("Tiempo de ejecución: " + tiempo + "ms\n");
	 return camino;
	 }
	}


