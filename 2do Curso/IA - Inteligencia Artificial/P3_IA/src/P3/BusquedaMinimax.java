package P3;

/*
 * =====================================================
 * NUEVOS ALGORITMOS CON ADVERSARIO (CÃLCULO DINÃMICO)
 * =====================================================
 */

class BusquedaMinimax {
	private int maxProfundidad = 4; // Profundidad máxima

	private boolean comprobarAccion(Entorno mapa, String accion, int f, int c) {

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

	public String pensar(Entorno mapa, char jugador) {
		String mejorAccion = null;
		int mejorValor = Integer.MIN_VALUE;

		String acciones[] = { "N", "S", "E", "O" }; // Movimientos disponibles
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 }; // Desplazamientos en fila y columna

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF(jugador);
			int c = mapa.getAgenteC(jugador);
			if (comprobarAccion(mapa, acciones[i], f + df[i], c + dc[i])) {
				mapa.moverAgente(jugador, acciones[i]);
				int valor = minValor(mapa, maxProfundidad - 1);
				mapa.deshacerMovimiento(jugador, acciones[i]);

				if (valor > mejorValor) {
					mejorValor = valor;
					mejorAccion = acciones[i];
				}
			}

		}

		// LLamat a MINMAX con la profundidad adecuada, etc..
		return mejorAccion;
	}

	public int minValor(Entorno mapa, int profundidad) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		int mejorValor = Integer.MAX_VALUE;
		boolean puede = false;
		String acciones[] = { "N", "S", "E", "O" }; // Movimientos disponibles
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 }; // Desplazamientos en fila y columna

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B');
			if (comprobarAccion(mapa, acciones[i], f + df[i], c + dc[i])) {
				puede = true;
				mapa.moverAgente('B', acciones[i]);
				int valor = maxValor(mapa, profundidad - 1);
				mapa.deshacerMovimiento('B', acciones[i]);

				mejorValor = Math.min(mejorValor, valor);
			}
		}

		if (!puede)
			return 1000;

		return mejorValor;
	}

	public int maxValor(Entorno mapa, int profundidad) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		int mejorValor = Integer.MIN_VALUE;
		boolean puede = false;
		String acciones[] = { "N", "S", "E", "O" }; // Movimientos disponibles
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 }; // Desplazamientos en fila y columna

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A');
			if (comprobarAccion(mapa, acciones[i], f + df[i], c + dc[i])) {
				puede = true;
				mapa.moverAgente('A', acciones[i]);
				int valor = minValor(mapa , profundidad - 1);
				mapa.deshacerMovimiento('A', acciones[i]);

				mejorValor = Math.max(mejorValor, valor);
			}
		}

		if (!puede)
			return -1000;

		return mejorValor;
	}
}