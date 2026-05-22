package AAD;
import java.util.*;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
/*
 * =====================================================
 * AGENTE DUMMY DE PRUEBA
 * =====================================================
 */
/*
 * =====================================================
 * NUEVOS ALGORITMOS CON ADVERSARIO (CÁLCULO DINÁMICO)
 * =====================================================
 */

class BusquedaMinimax {
    private int maxProfundidad = 4; // Profundidad máxima

    public String pensar(Entorno mapa, char jugador) {
        String mejorAccion = null;
        int mejorValor = Integer.MIN_VALUE;

        String[] acciones = { "N", "S", "E", "O" };
        for (String accion : acciones) {
            if (mapa.moverAgente(jugador, accion)) {
                int valor = minimax(mapa, maxProfundidad - 1, false, jugador);
                mapa.deshacerMovimiento(jugador, accion);

                if (valor > mejorValor) {
                    mejorValor = valor;
                    mejorAccion = accion;
                }
            }
        }
        return mejorAccion;
    }

    private int minimax(Entorno mapa, int profundidad, boolean esMax, char yo) {
        char rival = (yo == 'A') ? 'B' : 'A';
        char turnoActual = esMax ? yo : rival;

        if (profundidad == 0 || mapa.juegoTerminadoPara(turnoActual)) {
            return evaluar(mapa, yo);
        }

        int mejorValor = esMax ? Integer.MIN_VALUE : Integer.MAX_VALUE;
        String[] acciones = { "N", "S", "E", "O" };
        boolean hayMovimientos = false;

        for (String accion : acciones) {
            if (mapa.moverAgente(turnoActual, accion)) {
                hayMovimientos = true;
                int valor = minimax(mapa, profundidad - 1, !esMax, yo);
                mapa.deshacerMovimiento(turnoActual, accion);

                if (esMax) {
                    mejorValor = Math.max(mejorValor, valor);
                } else {
                    mejorValor = Math.min(mejorValor, valor);
                }
            }
        }

        if (!hayMovimientos) {
            return evaluar(mapa, yo);
        }

        return mejorValor;
    }

    private int evaluar(Entorno mapa, char yo) {
        char rival = (yo == 'A') ? 'B' : 'A';

        // Condiciones definitivas del juego (victoria/derrota)
        if (mapa.haGanado(yo))
            return 10000;
        if (mapa.haGanado(rival))
            return -10000;
        if (mapa.juegoTerminadoPara(yo))
            return -10000;
        if (mapa.juegoTerminadoPara(rival))
            return 10000;

        int misMovimientos = mapa.movimientosValidos(yo);
        int susMovimientos = mapa.movimientosValidos(rival);

        int distMetaMia = Math.abs(mapa.getAgenteC(yo) - mapa.getMetaCol(yo));
        int distMetaRival = Math.abs(mapa.getAgenteC(rival) - mapa.getMetaCol(rival));

        return (misMovimientos - susMovimientos) * 20 + (distMetaRival - distMetaMia);
    }
}