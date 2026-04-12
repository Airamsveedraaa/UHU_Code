package P2;
import java.util.Queue;
import java.util.PriorityQueue;
import java.util.List;
import java.util.LinkedList;
import java.util.Stack;

public abstract class Busqueda {
	 protected int tamMax=-1;
	 protected int nAbiertos;
	 protected long tIni,tFin,tiempo;
	 
	 protected List<String> reconstruirCamino(Nodo meta) {
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
				System.out.println("Solución encontrada usando A* Ponderado");
				System.out.println("Camino recorrido (x,y): " + coordenadas);	
				System.out.println("Coste total del camino: " + meta.g);
				System.out.println("Nodos expandidos: " + nAbiertos);
				System.out.println("Tamaño máximo de ABIERTOS: " + tamMax);
				System.out.println("Tiempo de ejecución: " + tiempo + "ms\n");
			return camino;
			}
}
