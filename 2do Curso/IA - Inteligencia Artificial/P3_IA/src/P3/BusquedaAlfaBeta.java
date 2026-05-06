package P3;

class BusquedaAlfaBeta extends Busqueda {
	private int maxProfundidad = 6;
	
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
				int valor = maxValor(mapa, maxProfundidad - 1, alfa, beta);
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

		int valor = Integer.MIN_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A');
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
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
			return super.evaluar(mapa);
		}

		super.nodosVisitados++;

		int valor = Integer.MAX_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B');
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
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