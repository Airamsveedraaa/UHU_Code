package P3;

class BusquedaAlfaBeta {
	private int maxProfundidad = 6;

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
		int alfa = -1000;
		int beta = +1000;

		String[] acciones = { "N", "S", "E", "O" };
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 };

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF(jugador);
			int c = mapa.getAgenteC(jugador);

			if (comprobarAccion(mapa, acciones[i], f + df[i], c + dc[i])) {
				mapa.moverAgente(jugador, acciones[i]);
				int valor = maxValor(mapa, maxProfundidad - 1, alfa, beta);
				mapa.deshacerMovimiento(jugador, acciones[i]);
				if (valor > mejorValor) {
					mejorValor = valor;
					mejorAccion = acciones[i];
				}
			}
		}
		// alfabeta
		return mejorAccion;
	}

	public int maxValor(Entorno mapa, int profundidad, int alfa, int beta) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		int valor = Integer.MIN_VALUE;
		String[] acciones = { "N", "S", "E", "O" };
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 };
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A');
			if (comprobarAccion(mapa, acciones[i], f + df[i], c + dc[i])) {
				puede = true;
				mapa.moverAgente('A', acciones[i]);
				valor = Math.max(valor, minValor(mapa, profundidad - 1, alfa, beta));
				alfa = Math.max(alfa, valor);
				mapa.deshacerMovimiento('A', acciones[i]);
				if (alfa >= beta)
					return valor;
			}
		}
		if (!puede)
			return -1000;
		return valor;
	}

	public int minValor(Entorno mapa, int profundidad, int alfa, int beta) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		int valor = Integer.MAX_VALUE;
		String[] acciones = { "N", "S", "E", "O" };
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 };
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B');
			if (comprobarAccion(mapa, acciones[i], f + df[i], c + dc[i])) {
				puede = true;
				mapa.moverAgente('B', acciones[i]);
				valor = Math.min(valor, maxValor(mapa, profundidad - 1, alfa, beta));
				beta = Math.min(beta, valor);
				mapa.deshacerMovimiento('B', acciones[i]);
				if (alfa >= beta)
					return valor;
			}
		}
		if (!puede)
			return +1000;
		return valor;
	}
}