package P2;
import java.util.List;
import java.util.LinkedList;

public abstract class AgenteBusquedaXX {


	class BusquedaAnchura {
		 private List<Nodo> Abiertos=new LinkedList<>();
		 private List<Nodo> Cerrados=new LinkedList<>();
		 
	 public List<String> resolver(Entorno mapa) {


		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,0);
		 Abiertos.add(inicial);
		 int paso=1;
		 while(Abiertos.size()>0) {
			  List<Nodo> Hijos= new LinkedList();
			 Nodo Actual=Abiertos.removeFirst();
			 Cerrados.add(Actual);
			 
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 return reconstruirCamino(Actual);
			 }
			 else {
				 
				int [] df= {-1,+1,0,0};
				int [] dc= {0,0,+1,-1}; //Offsets en las 4 direcciones
				String [] Dirs= {"N","S","E","O"};
				int [] costes= {2,1,1,2}; //costos por movimiento
				
				//rellenar sucesores
				for(int i=0;i<4;i++) {
					int nf=Actual.f + df[i];
					int nc=Actual.c + dc[i];
					if(mapa.esTransitable(nf, nc)) //si es transitable (no # ni .), se valora
					{
						Nodo hijo=new Nodo(nf,nc,Actual,Dirs[i],Actual.g+costes[i],0);
						Hijos.add(hijo);
					
					if(!Cerrados.contains(hijo)) {
						//si no tiene al hijo, no ha sido valorado aun
						//no es un repetido en resumidas cuentas
						Abiertos.add(hijo);
					}
					}
					
				}
				System.out.println("Generados hijos: (" + Hijos + ")");
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				System.out.println("--- ESTADÍSTICAS FINALES ---");
				System.out.println("Solución encontrada usando");
				paso++;
			 }
		 }
	 return null;
	 }
	 private List<String> reconstruirCamino(Nodo meta) {
	 LinkedList<String> camino = new LinkedList<>();
	 Nodo actual = meta;
	 while (actual.padre != null) {
	 camino.addFirst(actual.accion);
	 actual = actual.padre;
	 }
	 System.out.println("Coste total: " + meta.g);
	 return camino;
	 }
	}
}

