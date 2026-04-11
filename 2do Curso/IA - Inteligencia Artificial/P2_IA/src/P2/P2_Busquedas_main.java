package P2;
import java.util.*;

public class P2_Busquedas_main {

	    // --- MAPAS DE PRUEBA ---
	    
	    // Mapa trampa: La casilla (1,1) al Este lleva a un callejón sin salida
	     static final String mapaTexto1=
	    		"#######\n" +
	    		"#E    #\n" +
	    	    "# ### #\n" +
	    		"#   #S#\n" +
	    		"#######";
	    
	     static final String mapaTexto2=
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
	        // String mapaActual = ;
	        String mapaActual = mapaTexto2;

	        Entorno juego = new Entorno(mapaActual);
	        
	     // 2. Elegir Agente (Descomentar el que se quiera probar)
	        AgenteBusqueda agente= new AgenteBusqueda();
	        System.out.println("--- Inicio de la Simulación ---");
	        int ciclos = 0;
	        boolean juegoActivo = true;
	        // BUCLE DE SIMULACIÓN
	        while (juegoActivo && ciclos < 100) {
	        System.out.println("\n\n--- Ciclo " + ciclos + " ---");
	        juego.dibujar();
	        // El agente decide
	        String accion = agente.pensar(juego);
	        
	        if(accion==null) {
	        	System.out.println("El agente se ha quedado sin plan o no encontró ruta");
	        	break;
	        }
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
