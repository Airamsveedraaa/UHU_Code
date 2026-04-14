package P2;
import java.util.List;
import java.util.LinkedList;

public class BusquedaAnchura extends Busqueda{
		 private List<Nodo> Abiertos=new LinkedList<>();
		 private List<Nodo> Cerrados=new LinkedList<>();
		 
		 private List<Nodo> getSucesores(Nodo Actual, Entorno mapa){
				
			 List<Nodo> sucesores=new LinkedList();
			 int f=Actual.f;
			 int c=Actual.c;
			 int g=Actual.g; //f c y g del nodo en ese momento.
			 
			 //si es transitabnle la añadimos como sucesor con sus valores, IDEM para las 4 direcciones cambiando el coste del camino.
			 if(mapa.esTransitable(f -1, c)) {sucesores.add(new Nodo(f-1,c,Actual,"N",g+super.costeIZQ_ARRIBA,0));}
			 if(mapa.esTransitable(f +1, c)) {sucesores.add(new Nodo(f+1,c,Actual,"S",g+super.costeDER_ABAJO,0));}
			 if(mapa.esTransitable(f, c+1)) {sucesores.add(new Nodo(f,c+1,Actual,"E",g+super.costeDER_ABAJO,0));}
			 if(mapa.esTransitable(f, c-1)) {sucesores.add(new Nodo(f,c-1,Actual,"O",g+super.costeIZQ_ARRIBA,0));}
			 return sucesores;
		 }
		 
		 private List<Nodo> quitarRepetidos(List<Nodo> sucesores, List<Nodo> Cerrados, List<Nodo> Abiertos){
			
			 List<Nodo> noRepetidos=new LinkedList();
			 List<Nodo> repetidos=new LinkedList<>();
			 for(int i=0; i<sucesores.size(); i++) {
				 Nodo s=sucesores.get(i); //para comparaciones
			 if(!Cerrados.contains(s) && !Abiertos.contains(s)) {
				 //si no está en cerrados no es repetido, pero también hay que mirar si está o no en abiertos para evitar añadir un nodo duplicado que esté abierto en ese momento.
				 noRepetidos.add(s);
			 }
			 else {
				 repetidos.add(s);
			 }
			 }
			 if(!repetidos.isEmpty()) System.out.println("Sucesores Repetidos descartados: " + "(" + repetidos + ")");
			 return noRepetidos;
		 }
		 
	 public List<String> resolver(Entorno mapa) {

		 List<Nodo> sucesores=new LinkedList();
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,0);
		 Abiertos.add(inicial);
		 int paso=1; //para el numero de paso, usado en traza.
		 System.out.println("Iniciando busqueda BFS...");
		 System.out.println(" Origen: " + "(" + inicial.f + "," + inicial.c + ")  -> Meta: " + "(" + mapa.metaF + "," + mapa.metaC + ")\n\n" );
		 this.tIni=System.currentTimeMillis(); //calculo de tiempo de ejecucion.
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > this.tamMax) this.tamMax=tam; //obtenemos el tamaño maximo de la estructura abiertos.
			 this.nAbiertos++; //numero de nodos abiertos
			 Nodo Actual=Abiertos.removeFirst();
			 Cerrados.add(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 //si es la meta calculamos el tiempo de ejecucion y reconstruimos el camino mostrando las estadísticas.
				 this.tFin=System.currentTimeMillis();
				 this.tiempo=this.tFin-this.tIni;
				 return this.reconstruirCamino(Actual,"BFS");
			 }
			 else {
				 //si no es la meta obtenemos los sucesores y tratamos los repetidos y volvemos a hacer otra pasada
				 	sucesores=getSucesores(Actual,mapa);
				 	sucesores=quitarRepetidos(sucesores,Cerrados, Abiertos);
				 	Abiertos.addAll(sucesores);
					
				}
			 //mostramos para cada pasada los sucesores y el estado de las estructuras
				System.out.println("Generados hijos: (" + sucesores + ")");
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				paso++;
		 }
		 //si no encuentra la solución calculamos tiempo de ejecución y mostramos el mensaje de error correspondiente.
		 this.tFin=System.currentTimeMillis();
		 this.tiempo=tFin-tIni;
		 System.out.println("Solución no encontrada usando BFS");
		 System.out.println("Nodos Expandidos: " + this.nAbiertos);
		 System.out.println("Tiempo de ejecucion: " + this.tiempo + "ms\n");
	 return null;
	 }
}


