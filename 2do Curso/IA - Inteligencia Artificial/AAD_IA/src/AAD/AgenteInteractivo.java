package AAD;
import java.util.*;

/*
 * =====================================================
 * AGENTE INTERACTIVO (PLAN B MANUAL)
 * =====================================================
 */
class AgenteInteractivo {

    public String pensar(Entorno mapa, char jugador) {
        System.out.println("\n[Agente Interactivo] Generando prompt para tu turno...");

        int f = mapa.getAgenteF(jugador);
        int c = mapa.getAgenteC(jugador);
        int metaCol = mapa.getMetaCol(jugador);

        List<String> validas = new ArrayList<>();
        String[] acciones = { "N", "S", "E", "O" };
        for (String accion : acciones) {
            int nf = f, nc = c;
            if (accion.equals("N"))
                nf--;
            if (accion.equals("S"))
                nf++;
            if (accion.equals("E"))
                nc++;
            if (accion.equals("O"))
                nc--;
            if (mapa.esTransitable(nf, nc)) {
                validas.add(accion);
            }
        }

        if (validas.isEmpty())
            return null;

        // --- SELECCIÓN DE ESTRATEGIA ---
        String prompt = buildEstrategia1_Basica(f, c, metaCol, validas, mapa);

        // Limpiamos los saltos de línea para mostrarlo bonito por consola
        String promptLimpio = prompt.replace("\\n", "\n");

        System.out.println("\n========== COPIA ESTE PROMPT EN EL LLM ==========");
        System.out.println(promptLimpio);
        System.out.println("=================================================");

        System.out.println("\nPega la respuesta completa del LLM aquí abajo.");
        System.out.println("(Cuando termines, escribe la palabra FIN en una nueva línea y pulsa Enter):");

        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        StringBuilder respuestaLLM = new StringBuilder();

        while (true) {
            String linea = scanner.nextLine();
            if (linea.trim().equalsIgnoreCase("FIN")) {
                break;
            }
            respuestaLLM.append(linea).append("\n");
        }

        String extraccion = respuestaLLM.toString();

        System.out.println("\n[Agente Interactivo] Razonamiento introducido:\n" + extraccion);
        String decision = interpretarAccion(extraccion, validas);

        return decision;
    }

    // Estrategia 1: Básica, solo sabe dónde está y qué puede hacer
    private String buildEstrategia1_Basica(int f, int c, int metaCol, List<String> validas, Entorno mapa) {
        StringBuilder sb = new StringBuilder();
        sb.append("Estás en un laberinto estilo Tron. Tu posición actual es fila ").append(f).append(", columna ")
                .append(c).append(".\\n");
        sb.append("Tu objetivo es cruzar el mapa y llegar a cualquier casilla que esté en la columna ").append(metaCol)
                .append(".\\n");
        sb.append("Los movimientos válidos que puedes hacer sin chocar ahora mismo son: ")
                .append(String.join(", ", validas)).append(".\\n");
        sb.append("Analiza qué movimiento te acerca más a la columna ").append(metaCol).append(
                ". Explica brevemente tu razonamiento (1-2 líneas). Luego, OBLIGATORIAMENTE, en la última línea escribe: ACCION: X (donde X es N, S, E u O).");
        return sb.toString();
    }

    private String interpretarAccion(String texto, List<String> validas) {
        texto = texto.toUpperCase();
        if (texto.contains("ACCION: N") || texto.contains("ACCIÓN: N"))
            return "N";
        if (texto.contains("ACCION: S") || texto.contains("ACCIÓN: S"))
            return "S";
        if (texto.contains("ACCION: E") || texto.contains("ACCIÓN: E"))
            return "E";
        if (texto.contains("ACCION: O") || texto.contains("ACCIÓN: O"))
            return "O";

        String[] palabras = texto.split("\\s+");
        for (String p : palabras) {
            p = p.replaceAll("[^A-Z]", "");
            if ((p.equals("N") || p.equals("NORTE")) && validas.contains("N"))
                return "N";
            if ((p.equals("S") || p.equals("SUR")) && validas.contains("S"))
                return "S";
            if ((p.equals("E") || p.equals("ESTE")) && validas.contains("E"))
                return "E";
            if ((p.equals("O") || p.equals("OESTE")) && validas.contains("O"))
                return "O";
        }
        return validas.get(0);
    }
}
