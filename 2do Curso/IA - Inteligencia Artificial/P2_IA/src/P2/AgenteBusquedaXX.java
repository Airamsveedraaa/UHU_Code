package P2;
import java.util.List;
import java.util.LinkedList;

public abstract class AgenteBusquedaXX {


	class BusquedaAnchura {
	 public List<String> resolver(Entorno mapa) {
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

