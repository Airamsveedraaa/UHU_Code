package P3;

/*
 * =====================================================
 * NUEVOS ALGORITMOS CON ADVERSARIO (CÃLCULO DINÃMICO)
 * =====================================================
 */

class BusquedaMinimax extends Busqueda {
	private int maxProfundidad = 4; // Profundidad máxima
	
	public BusquedaMinimax(int modoHeuristica) {
		super(modoHeuristica);
	}

	public String pensar(Entorno mapa, char jugador) {
		String mejorAccion = null;
		int mejorValor = Integer.MIN_VALUE;

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF(jugador);
			int c = mapa.getAgenteC(jugador);
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
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
		System.out.println("Nodos visitados: " + nodosVisitados);
		nodosVisitados = 0;
		return mejorAccion;
	}

	public int minValor(Entorno mapa, int profundidad) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return super.evaluar(mapa);
		}

		super.nodosVisitados++;

		int mejorValor = Integer.MAX_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B');
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
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
			return super.evaluar(mapa);
		}

		super.nodosVisitados++;

		int mejorValor = Integer.MIN_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A');
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				puede = true;
				mapa.moverAgente('A', acciones[i]);
				int valor = minValor(mapa, profundidad - 1);
				mapa.deshacerMovimiento('A', acciones[i]);

				mejorValor = Math.max(mejorValor, valor);
			}
		}

		if (!puede)
			return -1000;

		return mejorValor;
	}
}