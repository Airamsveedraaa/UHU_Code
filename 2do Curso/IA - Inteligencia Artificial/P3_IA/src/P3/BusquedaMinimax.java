package P3;

/*
 * =====================================================
 * NUEVOS ALGORITMOS CON ADVERSARIO (CÃLCULO DINÃMICO)
 * =====================================================
 */

class BusquedaMinimax {
	private int maxProfundidad = 4; // Profundidad mÃ¡xima

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

	public String resolver(Entorno mapa, char jugador) {
		String mejorAccion = null;
		int mejorValor = Integer.MIN_VALUE;

		String Movi[] = { "N", "S", "E", "O" };
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 };

		for (int i = 0; i < 4; i++) {
			int f = mapa.agenteAF;
			int c = mapa.agenteAC;
			if (comprobarAccion(mapa, Movi[i], f + df[i], c + dc[i])) {
				mapa.moverAgente('A', Movi[i]);
				int valor = minValor(mapa, maxProfundidad - 1);
				mapa.deshacerMovimiento('A', Movi[i]);

				if (valor > mejorValor) {
					mejorValor = valor;
					mejorAccion = Movi[i];
				}
			}

		}

		// LLamat a MINMAX con la profundidad adecuada, etc..
		return mejorAccion;
	}

	private int minValor(Entorno mapa, int profundidad) {

		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			//si profundidad 0 es una hoja y se evalua
			//si ha acabado el juego para cualquier jugador se evalua tambien
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		int peor = Integer.MAX_VALUE; //maximo valor para que se cumpla la condicion en una iteracion al menos
		boolean Movimiento = false;

		String Movi[] = { "N", "S", "E", "O" };
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 };

		for (int i = 0; i < 4; i++) {
			int f = mapa.agenteBF;
			int c = mapa.agenteBC;

			if (comprobarAccion(mapa, Movi[i], f + df[i], c + dc[i])) {
				//para cada movimiento comprobar si es valido o no
				//y comprobar si nuestro valor obtenido llamando a max es mejor o peor que el calculado
				Movimiento = true;
				mapa.moverAgente('B', Movi[i]);
				int valor = maxValor(mapa, profundidad - 1);
				mapa.deshacerMovimiento('B', Movi[i]);
				peor = Math.min(peor, valor);
			}
		}

		if (!Movimiento)
			//Si no tenemos movimientos disponibles devolvemos un valor alto indicando que gana Max
			return 1000;
		return peor;
	}

	private int maxValor(Entorno mapa, int profundidad) {

		if (profundidad == 0 || mapa.juegoTerminadoPara('A') || mapa.juegoTerminadoPara('B')) {
			//si la profundidad es 0 quiere decir que es una hoja y hay que evaluar, de igual manera
			//si ha acabado el juego para A o B se evalua los movimientos validos de A y de B
			return mapa.movimientosValidos('A') - mapa.movimientosValidos('B');
		}

		int mejor = Integer.MIN_VALUE; //minimo valor para que al menos una iteracion cumpla la condicion
		boolean Movimiento = false;

		String Movi[] = { "N", "S", "E", "O" };
		int df[] = { -1, 1, 0, 0 };
		int dc[] = { 0, 0, 1, -1 };

		for (int i = 0; i < 4; i++) {
			int f = mapa.agenteAF;
			int c = mapa.agenteAC;

			if (comprobarAccion(mapa, Movi[i], f + df[i], c + dc[i])) {
				
				//Para cada accion comprobamos si es un movimiento valido
				//si es valido llamamos a min para ver si nuestro valor es mejor o peor que el que devuelve min
				Movimiento = true;
				mapa.moverAgente('A', Movi[i]);
				int valor = minValor(mapa, profundidad - 1);
				mapa.deshacerMovimiento('A', Movi[i]);
				mejor = Math.max(mejor, valor);
			}
		}

		if (!Movimiento)
			//si no tenemos movimientos disponibles quiere decir que hemos perdido
			return -1000;
		return mejor;
	}

}
