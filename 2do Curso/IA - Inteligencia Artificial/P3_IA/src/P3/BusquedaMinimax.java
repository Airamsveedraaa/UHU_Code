package P3;

/*
 * =====================================================
 * ALGORITMO MINIMAX
 * =====================================================
 */

class BusquedaMinimax extends Busqueda {

	// Constructor
	public BusquedaMinimax(int modoHeuristica) {
		super(modoHeuristica);
	}

	// Método pensar
	public String pensar(Entorno mapa, char jugador) {
		String mejorAccion = null;
		int mejorValor = Integer.MIN_VALUE; // parámetros de inicialización

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF(jugador);
			int c = mapa.getAgenteC(jugador); // Coordenadas del agente
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				// Si el movimiento es posible, movemos, calculamos con las sucesivas llamadas y
				// deshacemos
				mapa.moverAgente(jugador, acciones[i]);
				int valor = minValor(mapa, super.maxProfundidad - 1);
				mapa.deshacerMovimiento(jugador, acciones[i]);

				if (valor > mejorValor) {
					mejorValor = valor;
					mejorAccion = acciones[i];
				}
			}

		}

		// Mostrar nodos visitados por turnos
		System.out.println("Nodos visitados: " + nodosVisitados);
		nodosVisitados = 0;
		return mejorAccion;
	}

	// Método MinValor
	public int minValor(Entorno mapa, int profundidad) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			// Si es profundidad limite o acaba juego, devolver utilidad
			return super.evaluar(mapa);
		}

		super.nodosVisitados++; // Incrementar nodos por turno

		int mejorValor = Integer.MAX_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF('B');
			int c = mapa.getAgenteC('B'); // Coordenadas del Agente
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				// Si es valido, mueve, calcula y deshace
				puede = true;
				mapa.moverAgente('B', acciones[i]);
				int valor = maxValor(mapa, profundidad - 1);
				mapa.deshacerMovimiento('B', acciones[i]);

				mejorValor = Math.min(mejorValor, valor); // Coger mejor valor de B
			}
		}

		if (!puede) // Si no hay movimientos, devolver "+infinito"
			return 1000;

		return mejorValor;
	}

	// Método MaxValor, IDEM a MinValor pero buscamos máximo
	public int maxValor(Entorno mapa, int profundidad) {
		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			// Si es nodo terminal o fin de juego devolver utilidad
			return super.evaluar(mapa);
		}

		super.nodosVisitados++; // Incrementar nodos visitados

		int mejorValor = Integer.MIN_VALUE;
		boolean puede = false;

		for (int i = 0; i < 4; i++) {

			int f = mapa.getAgenteF('A');
			int c = mapa.getAgenteC('A'); // Coordenadas actuales del Agente
			if (super.comprobarAccion(mapa, super.acciones[i], f + super.df[i], c + super.dc[i])) {
				// Si es valido, mover, calcular y deshacer
				puede = true;
				mapa.moverAgente('A', acciones[i]);
				int valor = minValor(mapa, profundidad - 1);
				mapa.deshacerMovimiento('A', acciones[i]);

				mejorValor = Math.max(mejorValor, valor); // Coger mejor valor, maximo en este caso
			}
		}

		if (!puede) // Si no hay movimientos, devolver "-infinito"
			return -1000;

		return mejorValor;
	}
}