package P2;
import java.util.Stack;
import java.util.List;
import java.util.LinkedList;

public class BusquedaProfundidad extends Busqueda{
		 private Stack<Nodo> Abiertos=new Stack<>();
		 private List<Nodo> Cerrados=new LinkedList<>();

		 private Stack<Nodo> getSucesores(Nodo Actual, Entorno mapa){
				
			 Stack<Nodo> sucesores=new Stack<>();
			 int f=Actual.f;
			 int c=Actual.c;
			 int g=Actual.g; //f c y g del nodo en ese momento
			 
			 //IDEM a BFS totalmente.
			 if(mapa.esTransitable(f -1, c)) {sucesores.push(new Nodo(f-1,c,Actual,"N",g+super.costeIZQ_ARRIBA,0));}
			 if(mapa.esTransitable(f +1, c)) {sucesores.push(new Nodo(f+1,c,Actual,"S",g+super.costeDER_ABAJO,0));}
			 if(mapa.esTransitable(f, c+1)) {sucesores.push(new Nodo(f,c+1,Actual,"E",g+super.costeDER_ABAJO,0));}
			 if(mapa.esTransitable(f, c-1)) {sucesores.push(new Nodo(f,c-1,Actual,"O",g+super.costeIZQ_ARRIBA,0));}
			 return sucesores;
		 }
		 
		 //IDEM a BFS totalmente 
		 private Stack<Nodo> quitarRepetidos(Stack<Nodo> sucesores, List<Nodo> Cerrados, Stack<Nodo> Abiertos){
			
			 Stack<Nodo> noRepetidos=new Stack();
			 List<Nodo> repetidos=new LinkedList<>();
			 for(int i=0; i<sucesores.size(); i++) {
				 Nodo s=sucesores.get(i);
			 if(!Cerrados.contains(s) && !Abiertos.contains(s)) {
				 noRepetidos.push(s);
			 }
			 else {
				 repetidos.add(s);
			 }
			 }
			 if(!repetidos.isEmpty()) System.out.println("Sucesores Repetidos descartados: " + "(" + repetidos + ")");
			 return noRepetidos;
		 }
		 
		 //IDEM a BFS todo el código con la diferencia de que usaremos pilas (Stacks) en vez de listas como estructuras, el resto es todo lo mismo.
	 public List<String> resolver(Entorno mapa) {

		 Stack<Nodo> sucesores=new Stack();
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,0);
		 Abiertos.push(inicial);
		 int paso=1;
		 System.out.println("Iniciando busqueda DFS...");
		 System.out.println(" Origen: " + "(" + inicial.f + "," + inicial.c + ")  -> Meta: " + "(" + mapa.metaF + "," + mapa.metaC + ")\n\n" );
		 this.tIni=System.currentTimeMillis();
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > this.tamMax) this.tamMax=tam; 
			 this.nAbiertos++;
			 Nodo Actual=Abiertos.pop();
			 Cerrados.add(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 this.tFin=System.currentTimeMillis();
				 this.tiempo=this.tFin-this.tIni;
				 return this.reconstruirCamino(Actual,"DFS");
			 }
			 else {
				 	sucesores=getSucesores(Actual,mapa);
				 	sucesores=quitarRepetidos(sucesores,Cerrados,Abiertos);
					System.out.println("Generados hijos: (" + sucesores + ")");
					int n=sucesores.size();
					//bucle auxiliar para poder transferir todos los elementos 
				 	for(int i=0; i<n;i++) {
				 		Abiertos.push(sucesores.pop());
				 	}
					
				}
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				paso++;
		 }
		 this.tFin=System.currentTimeMillis();
		 this.tiempo=this.tFin-this.tIni;
		 System.out.println("Solución no encontrada usando DFS");
		 System.out.println("Nodos Expandidos: " + this.nAbiertos);
		 System.out.println("Tiempo de ejecucion: " + this.tiempo + "ms\n");
	 return null;
	 }
	}


