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
			 int g=Actual.g;
			 
			 if(mapa.esTransitable(f -1, c)) {sucesores.add(new Nodo(f-1,c,Actual,"N",g+2,0));}
			 if(mapa.esTransitable(f +1, c)) {sucesores.add(new Nodo(f+1,c,Actual,"S",g+1,0));}
			 if(mapa.esTransitable(f, c+1)) {sucesores.add(new Nodo(f,c+1,Actual,"E",g+1,0));}
			 if(mapa.esTransitable(f, c-1)) {sucesores.add(new Nodo(f,c-1,Actual,"O",g+2,0));}
			 return sucesores;
		 }
		 
		 private List<Nodo> quitarRepetidos(List<Nodo> sucesores, List<Nodo> Cerrados, List<Nodo> Abiertos){
			
			 List<Nodo> noRepetidos=new LinkedList();
			 for(int i=0; i<sucesores.size(); i++) {
				 Nodo s=sucesores.get(i);
			 if(!Cerrados.contains(s) && !Abiertos.contains(s)) {
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
		 System.out.println("Iniciando busqueda BFS...");
		 System.out.println(" Origen: " + "(" + inicial.f + "," + inicial.c + ")  -> Meta: " + "(" + mapa.metaF + "," + mapa.metaC + ")\n\n" );
		 tIni=System.currentTimeMillis();
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > tamMax) tamMax=tam;
			 nAbiertos++;
			 Nodo Actual=Abiertos.removeFirst();
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
				 	sucesores=quitarRepetidos(sucesores,Cerrados, Abiertos);
				 	Abiertos.addAll(sucesores);
					
				}
				System.out.println("Generados hijos: (" + sucesores + ")");
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
}


