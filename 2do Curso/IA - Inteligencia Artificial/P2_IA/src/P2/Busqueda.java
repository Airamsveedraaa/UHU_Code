package P2;
import java.util.List;
import java.util.LinkedList;


public abstract class Busqueda {
	 protected int tamMax=-1; //para tamaño maximo de la estructura abiertos
	 protected int nAbiertos; //para numero de nodos expandidos.
	 protected long tIni,tFin,tiempo; //variables auxiliares para calculo del tiempo de ejecucion.
	 protected final int costeIZQ_ARRIBA=2;
	 protected final int costeDER_ABAJO=1; //costes de los movimientos.
	 
	 protected List<String> reconstruirCamino(Nodo meta, String algoritmo) {
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
				System.out.println("Solución encontrada usando " + algoritmo);
				System.out.println("Camino recorrido (x,y): " + coordenadas);	
				System.out.println("Coste total del camino: " + meta.g);
				System.out.println("Nodos expandidos: " + nAbiertos);
				System.out.println("Tamaño máximo de ABIERTOS: " + tamMax);
				System.out.println("Tiempo de ejecución: " + tiempo + "ms\n");
			return camino;
			}
}
