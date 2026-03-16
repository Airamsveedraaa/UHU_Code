package P0;

import java.util.*;


public class Tron_P0_BaseSimple {

    // --- MAPAS DE PRUEBA ---
    
    // Mapa trampa: La casilla (1,1) al Este lleva a un callejón sin salida
    static final String MAPA_CALLEJON =
            "#########\n" +
            "#A      #\n" + 
            "# ##### #\n" + 
            "# #   # #\n" + 
            "#     S #\n" +
            "#########";

    static final String MAPA_GRANDE =
            "####################\n" +
            "#A  #              #\n" +
            "# # # ###### ##### #\n" +
            "# #   #      #     #\n" +
            "# ##### ###### ### #\n" +
            "#     #        #   #\n" +
            "# ### ######## # # #\n" +
            "#   #          #   #\n" +
            "# ############## S #\n" +
            "####################";

    public static void main(String[] args) throws InterruptedException {

        // 1. SELECCIONAR MAPA
        // String mapaActual = MAPA_CALLEJON;
        String mapaActual = MAPA_GRANDE;

        Entorno juego = new Entorno(mapaActual);
        
     // 2. Elegir Agente (Descomentar el que se quiera probar)
        //AgenteInteractivo agente= new AgenteInteractivo();
         //AgenteReactivo agente = new AgenteReactivo();
        AgenteDeliberativo2B agente = new AgenteDeliberativo2B(juego.filas, juego.cols);
        //AgenteDeliberativo2A agente= new AgenteDeliberativo2A();
        //AgenteGreedy agente= new AgenteGreedy();
        System.out.println("--- Inicio de la Simulación ---");
        int ciclos = 0;
        boolean juegoActivo = true;
        // BUCLE DE SIMULACIÓN
        while (juegoActivo && ciclos < 200) {
        juego.dibujar();
        // El agente decide
        String accion = agente.pensar(juego);
        // El entorno aplica el movimiento
        boolean movimientoExitoso = juego.moverAgente(accion);
        System.out.println("Ciclo " + ciclos + " | Acción: " +
       accion);

        if (!movimientoExitoso) {
        System.out.println(">>> ¡CRASH! El agente se ha chocado.");
        juegoActivo = false;
        } else if (juego.hemosGanado()) {
        System.out.println(">>> ¡VICTORIA! Salida encontrada.");
        juego.dibujar();
        juegoActivo = false;
        }
        Thread.sleep(300); // Retardo para animación
        ciclos++;
        }
        }
       }