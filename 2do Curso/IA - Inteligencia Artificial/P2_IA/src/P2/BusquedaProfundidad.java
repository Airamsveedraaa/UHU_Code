package P2;
import java.util.Stack;
import java.util.List;

public class BusquedaProfundidad extends Busqueda{
		 private Stack<Nodo> Abiertos=new Stack<>();
		 private Stack<Nodo> Cerrados=new Stack<>();

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
		 private Stack<Nodo> quitarRepetidos(Stack<Nodo> sucesores, Stack<Nodo> Cerrados, Stack<Nodo> Abiertos){
			
			 Stack<Nodo> noRepetidos=new Stack();
			 for(int i=0; i<sucesores.size(); i++) {
				 Nodo s=sucesores.get(i);
			 if(!Cerrados.contains(s) && !Abiertos.contains(s)) {
				 noRepetidos.push(s);
			 }
			 }
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
		 super.tIni=System.currentTimeMillis();
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > super.tamMax) super.tamMax=tam; 
			 super.nAbiertos++;
			 Nodo Actual=Abiertos.pop();
			 Cerrados.push(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 super.tFin=System.currentTimeMillis();
				 super.tiempo=super.tFin-super.tIni;
				 return super.reconstruirCamino(Actual,"DFS");
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
		 super.tFin=System.currentTimeMillis();
		 super.tiempo=super.tFin-super.tIni;
		 System.out.println("Solución no encontrada usando DFS");
		 System.out.println("Nodos Expandidos: " + super.nAbiertos);
		 System.out.println("Tiempo de ejecucion: " + super.tiempo + "ms\n");
	 return null;
	 }
	}


