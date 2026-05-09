package P3;

public abstract class Busqueda {

	protected int modoHeuristica;

	protected int nodosVisitados = 0;
	
	protected final int maxProfundidad = 6;


	protected String acciones[] = { "N", "S", "E", "O" }; // Movimientos disponibles
	protected int df[] = { -1, 1, 0, 0 };
	protected int dc[] = { 0, 0, 1, -1 }; // Desplazamientos en fila y columna

	protected Busqueda(int modoHeuristica) {
		this.modoHeuristica = modoHeuristica;
	}

	protected int evaluar(Entorno mapa) {

		if (modoHeuristica == 1) {
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		else {
			int movsA = mapa.movimientosValidos('A');
			int movsB = mapa.movimientosValidos('B');

			int distA = Math.abs(mapa.getAgenteC('A') - mapa.getMetaCol('A'));
			int distB = Math.abs(mapa.getAgenteC('B') - mapa.getMetaCol('B'));

			int valor = ((movsA - movsB) * 3) + (distB - distA);

			return valor;

		}
	}

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
