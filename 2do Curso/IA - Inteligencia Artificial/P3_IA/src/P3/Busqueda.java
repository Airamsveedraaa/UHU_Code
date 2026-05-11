package P3;

public abstract class Busqueda {

	// Parámetros utilizados por ambos algoritmos
	protected int modoHeuristica;

	protected int nodosVisitados = 0;

	protected final int maxProfundidad = 6;

	protected String acciones[] = { "N", "S", "E", "O" }; // Movimientos disponibles
	protected int df[] = { -1, 1, 0, 0 };
	protected int dc[] = { 0, 0, 1, -1 }; // Desplazamientos en fila y columna

	// Constructor para heurística
	protected Busqueda(int modoHeuristica) {
		this.modoHeuristica = modoHeuristica;
	}

	// Método auxiliar de evaluación de nodos terminales y hojas.
	protected int evaluar(Entorno mapa) {

		if (modoHeuristica == 1) {
			// Modo 1 utiliza solo movimientos disponibles
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		else {
			// Cualquier otro modo (0/2 por ej) utiliza movimientos y manhatan
			// Se le da mas importancia a movimientos (*3) ya que es la heuristica principal
			int movsA = mapa.movimientosValidos('A');
			int movsB = mapa.movimientosValidos('B');

			int distA = Math.abs(mapa.getAgenteC('A') - mapa.getMetaCol('A'));
			int distB = Math.abs(mapa.getAgenteC('B') - mapa.getMetaCol('B')); // Distancia de los agentes a columna
																				// rival que es la meta

			int valor = ((movsA - movsB) * 3) + (distB - distA);

			return valor;

		}
	}

	// Método auxiliar para comprobar acciones disponibles
	protected boolean comprobarAccion(Entorno mapa, String accion, int f, int c) {

		if (accion.equals("N")) {
			if (mapa.esTransitable(f, c))
				return true;
		}

		if (accion.equals("S")) {
			if (mapa.esTransitable(f, c))
				return true;
		}

		if (accion.equals("E")) {
			if (mapa.esTransitable(f, c))
				return true;
		}

		if (accion.equals("O")) {
			if (mapa.esTransitable(f, c))
				return true;
		}

		return false;
	}
}
