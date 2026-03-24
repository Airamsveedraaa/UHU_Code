package P2;
import java.util.List;
import java.util.LinkedList;

public abstract class AgenteBusquedaXX {


	class BusquedaAnchura {
	 public List<String> resolver(Entorno mapa) {
		 LinkedList<Nodo> Abiertos=new LinkedList<>();
		 List<Nodo> Cerrados=new LinkedList<>();
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,0);
		 Abiertos.add(inicial);
		 while(Abiertos.size()>0) {
			 Nodo Actual=Abiertos.removeFirst();
			 Cerrados.add(Actual);
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 return reconstruirCamino(Actual);
			 }
			 else {
				 List<Nodo> Sucesores= getsucesores(Actual);
				 sucesores= QuitarRepetidos(sucesores,Cerrados);
				 Abiertos.add(Sucesores);
			 }
		 }
	 // TODO: Lógica de inicialización, bucles, CERRADOS...
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

