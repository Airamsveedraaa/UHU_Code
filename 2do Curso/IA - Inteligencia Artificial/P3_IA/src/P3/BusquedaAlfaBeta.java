package P3;

class BusquedaAlfaBeta extends Busqueda {

	public BusquedaAlfaBeta(int modoHeuristica) {
		super(modoHeuristica);
	}

	public String pensar(Entorno mapa, char jugador) {
		String mejorAccion = null;
		int mejorValor = Integer.MIN_VALUE;
		int alfa = -1000;
		int beta = +1000;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF(jugador);
			int c = mapa.getAgenteC(jugador);

			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				mapa.moverAgente(jugador, acciones[i]);
				int valor = maxValor(mapa, super.maxProfundidad - 1, alfa, beta);
				mapa.deshacerMovimiento(jugador, acciones[i]);
				if (valor > mejorValor) {
					mejorValor = valor;
					mejorAccion = acciones[i];
				}
			}
		}
		// alfabeta
		System.out.println("Nodos visitados: " + nodosVisitados);
		nodosVisitados = 0;
		return mejorAccion;
	}

	public int maxValor(Entorno mapa, int profundidad, int alfa, int beta) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return super.evaluar(mapa);
		}

		super.nodosVisitados++;

		int mejorvalor = Integer.MIN_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A');
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				puede = true;
				mapa.moverAgente('A', acciones[i]);
				int valor = minValor(mapa, profundidad - 1, alfa, beta);
				mapa.deshacerMovimiento('A', acciones[i]);
				if (valor > mejorvalor)
					mejorvalor = valor;

				if (mejorvalor > alfa)
					alfa = mejorvalor;

				if (mejorvalor >= beta)
					break;
			}
		}
		if (!puede)
			return -1000;
		return mejorvalor;
	}

	public int minValor(Entorno mapa, int profundidad, int alfa, int beta) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return super.evaluar(mapa);
		}

		super.nodosVisitados++;

		int mejorvalor = Integer.MAX_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B');
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				puede = true;
				mapa.moverAgente('B', acciones[i]);
				int valor = maxValor(mapa, profundidad - 1, alfa, beta);
				mapa.deshacerMovimiento('B', acciones[i]);
				if (valor < mejorvalor)
					mejorvalor = valor;

				if (mejorvalor < beta)
					beta = mejorvalor;
				if (mejorvalor <= alfa)
					break;
			}
		}
		if (!puede)
			return +1000;
		return mejorvalor;
	}

}