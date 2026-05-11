package P3;

/*
 * =====================================================
 * ALGORITMO MINIMAX CON PODA ALFA-BETA
 * =====================================================
 */

class BusquedaAlfaBeta extends Busqueda {

	// Constructor
	public BusquedaAlfaBeta(int modoHeuristica) {
		super(modoHeuristica);
	}

	// Método pensar de Alfa-Beta
	public String pensar(Entorno mapa, char jugador) {
		String mejorAccion = null;
		int mejorValor = Integer.MIN_VALUE; // valores iniciales de los parámetros
		int alfa = -1000;
		int beta = +1000;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF(jugador);
			int c = mapa.getAgenteC(jugador); // Coordenadas actuales del agente

			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				// Si es una acción válida y posible, movemos y calculamos valores con maxvalor
				// y sucesivos
				mapa.moverAgente(jugador, acciones[i]);
				int valor = maxValor(mapa, super.maxProfundidad - 1, alfa, beta);
				mapa.deshacerMovimiento(jugador, acciones[i]); // Deshacer movimiento siempre
				if (valor > mejorValor) {
					mejorValor = valor;
					mejorAccion = acciones[i];
				}
			}
		}
		// Mostrar cuantos nodos visita por turno
		System.out.println("Nodos visitados: " + nodosVisitados);
		nodosVisitados = 0;
		return mejorAccion;
	}

	// Método maxValor
	public int maxValor(Entorno mapa, int profundidad, int alfa, int beta) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			// Si estamos en un nodo terminal o el juego acaba para alguno, devolver
			// utilidad del mapa
			return super.evaluar(mapa);
		}

		super.nodosVisitados++; // Incrementar nodos visitados por cada llamada

		int mejorvalor = Integer.MIN_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A'); // Coordenadas actuales del Agente
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				// Si es movimiento posible, movemos, calculamos y deshacemos
				puede = true;
				mapa.moverAgente('A', acciones[i]);
				int valor = minValor(mapa, profundidad - 1, alfa, beta);
				mapa.deshacerMovimiento('A', acciones[i]);
				if (valor > mejorvalor)
					mejorvalor = valor;

				if (mejorvalor > alfa)
					alfa = mejorvalor;

				if (mejorvalor >= beta) // Condicion de poda
					break;
			}
		}
		if (!puede) // Si no hay movimientos posibles, devuelve "-infinito"
			return -1000;
		return mejorvalor;
	}

	// Método Minvalor, IDEM a MaxValor pero buscamos minimo en vez de maximo
	public int minValor(Entorno mapa, int profundidad, int alfa, int beta) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			return super.evaluar(mapa); // Devolver utilidad del mapa
		}

		super.nodosVisitados++; // Nodos visitados

		int mejorvalor = Integer.MAX_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {
			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B'); // Coordenadas actuales
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				// Si puede, mueve,deshace y calcula
				puede = true;
				mapa.moverAgente('B', acciones[i]);
				int valor = maxValor(mapa, profundidad - 1, alfa, beta);
				mapa.deshacerMovimiento('B', acciones[i]);
				if (valor < mejorvalor)
					mejorvalor = valor;

				if (mejorvalor < beta)
					beta = mejorvalor;
				if (mejorvalor <= alfa) // condicion de poda, alfa>=beta, aqui mejorValor es beta asi que da igual cual
										// poner
					break;
			}
		}
		if (!puede) // Si no hay movimientos devuelve "+infinito"
			return +1000;
		return mejorvalor;
	}

}