package AAD;
import java.util.*;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
/*
 * =====================================================
 * AGENTE CON LLM (GEMINI PRO / FLASH)
 * =====================================================
 */
/*
 * =====================================================
 * AGENTE CON LLM (GROQ - LLAMA 3)
 * =====================================================
 */
class AgenteGroq {
    // ¡PON TU CLAVE DE GROQ AQUÍ! (https://console.groq.com/keys)
    private static final String API_KEY = "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";
    // Usamos Llama 3.1 8B porque es ultra rápido y muy capaz para esto
    private static final String MODEL_NAME = "llama-3.3-70b-versatile";
    private static final String URL = "https://api.groq.com/openai/v1/chat/completions";

    private HttpClient client;
    private int delayMilisegundos = 3000; // 3 segundos (llama-3.3-70b tiene rate limit más estricto)
    private List<String> historial = new ArrayList<>(); // Últimas posiciones visitadas

    public AgenteGroq() {
        this.client = HttpClient.newBuilder()
                .version(HttpClient.Version.HTTP_2)
                .connectTimeout(Duration.ofSeconds(10))
                .build();
    }

    public String pensar(Entorno mapa, char jugador) {
        System.out.println("[Agente Groq] Observando el entorno y conectando con la API...");

        // 1. Recopilar datos del entorno para el contexto
        int f = mapa.getAgenteF(jugador);
        int c = mapa.getAgenteC(jugador);
        int metaCol = mapa.getMetaCol(jugador);

        char rival = (jugador == 'A') ? 'B' : 'A';
        int rivalF = mapa.getAgenteF(rival);
        int rivalC = mapa.getAgenteC(rival);
        int metaRivalCol = mapa.getMetaCol(rival);

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
            return null; // No hay movimientos posibles

        // Construcción del texto del mapa
        StringBuilder mapaTexto = new StringBuilder();
        for (int i = 0; i < mapa.filas; i++) {
            mapaTexto.append(new String(mapa.grid[i])).append("\\n");
        }

        // Registrar posición actual en historial (máximo 3 últimas)
        historial.add("fila " + f + ", columna " + c);
        if (historial.size() > 3) historial.remove(0);

        // --- SELECCIÓN DE ESTRATEGIA ---
        String prompt = buildEstrategia1_Basica(f, c, metaCol, validas, mapa, jugador);

        // 2. Preparar el JSON para la petición en formato OpenAI (que es el que usa Groq)
        // Escape robusto: evita que saltos de línea u otros caracteres rompan el JSON
        String promptEscapado = prompt
                .replace("\\", "\\\\")
                .replace("\"", "\\\"")
                .replace("\n", "\\n")
                .replace("\r", "\\r")
                .replace("\t", "\\t");
        String jsonBody = "{"
                + "\"model\": \"" + MODEL_NAME + "\","
                + "\"messages\": [{\"role\": \"user\", \"content\": \"" + promptEscapado + "\"}],"
                + "\"temperature\": 0.0"
                + "}";

        // 3. Hacer la petición HTTP
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(URL))
                .header("Content-Type", "application/json")
                .header("Authorization", "Bearer " + API_KEY) // Groq usa Bearer Token
                .POST(HttpRequest.BodyPublishers.ofString(jsonBody))
                .build();

        String decision = validas.get(0); // Por defecto

        try {
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                String resBody = response.body();
                String extraccion = parsearRespuestaGroq(resBody);

                System.out.println("[Agente Groq] Razonamiento:\n" + extraccion + "\n");
                decision = interpretarAccion(extraccion, validas);
            } else {
                System.out.println("[Agente Groq] Error HTTP " + response.statusCode() + ": " + response.body());
            }

        } catch (Exception e) {
            System.out.println("[Agente Groq] Excepción al llamar a la API: " + e.getMessage());
        }

        // 4. Delay para el Rate Limit de Groq
        System.out.println("[Agente Groq] Esperando " + (delayMilisegundos / 1000.0) + "s (Rate Limit)...");
        try {
            Thread.sleep(delayMilisegundos);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        return decision;
    }

    // --- ESTRATEGIAS DE PROMPT ---

    // Estrategia táctica: Java decide la estrategia, el LLM elige la dirección concreta
    private String buildEstrategia1_Basica(int f, int c, int metaCol, List<String> validas, Entorno mapa, char jugador) {
        char rival = (jugador == 'A') ? 'B' : 'A';
        int rF = mapa.getAgenteF(rival);
        int rC = mapa.getAgenteC(rival);
        int rMeta = mapa.getMetaCol(rival);

        int distMia   = Math.abs(c - metaCol);
        int distRival = Math.abs(rC - rMeta);

        // Dirección textual hacia la meta
        String dirMeta = (metaCol > c) ? "Este (E)" : "Oeste (O)";

        // Mapa visual
        StringBuilder mapaVisual = new StringBuilder();
        for (int i = 0; i < mapa.filas; i++) {
            mapaVisual.append(new String(mapa.grid[i])).append("\n");
        }

        // Adyacencias
        int[][] dirs  = {{-1,0},{1,0},{0,1},{0,-1}};
        String[] noms = {"Norte (N)","Sur (S)","Este (E)","Oeste (O)"};
        StringBuilder adyacentes = new StringBuilder();
        for (int i = 0; i < 4; i++) {
            int nf = f + dirs[i][0], nc = c + dirs[i][1];
            String desc;
            if (nf < 0 || nf >= mapa.filas || nc < 0 || nc >= mapa.cols) desc = "borde";
            else {
                char celda = mapa.grid[nf][nc];
                if      (celda == '#')                    desc = "MURO-prohibido";
                else if (celda == 'a' || celda == 'b')    desc = "RASTRO-prohibido";
                else if (celda == 'A' || celda == 'B')    desc = "JUGADOR-prohibido";
                else                                      desc = "libre";
            }
            adyacentes.append(noms[i]).append(":").append(desc).append("  ");
        }

        // Salidas por destino y callejones
        List<String> callejones = new ArrayList<>();
        StringBuilder salidasInfo = new StringBuilder();
        for (String ac : validas) {
            int nf = f, nc = c;
            if (ac.equals("N")) nf--; if (ac.equals("S")) nf++;
            if (ac.equals("E")) nc++; if (ac.equals("O")) nc--;
            int salidas = 0;
            for (int[] d : dirs) {
                int df = nf + d[0], dc = nc + d[1];
                if (df == f && dc == c) continue;
                if (mapa.esTransitable(df, dc)) salidas++;
            }
            salidasInfo.append(ac).append(":").append(salidas).append("sal  ");
            if (salidas == 0) callejones.add(ac);
        }
        List<String> permitidos = new ArrayList<>(validas);
        permitidos.removeAll(callejones);

        // --- DECISIÓN ESTRATÉGICA: Java evalúa qué conviene este turno ---
        // Encerrar solo con ventaja clara (>3 col). En cualquier otro caso: ir a meta.
        String estrategia;
        String razonEstrategia;
        int ventaja = distRival - distMia; // positivo = yo voy mejor
        if (distMia <= 3) {
            estrategia = "AVANZAR A META";
            razonEstrategia = "Estas a solo " + distMia + " columnas de la meta (columna " + metaCol + "). Muevete hacia " + dirMeta + ".";
        } else if (ventaja >= 3) {
            estrategia = "ENCERRAR AL RIVAL";
            razonEstrategia = "Llevas " + ventaja + " columnas de ventaja. Intenta cortar el camino al rival.";
        } else if (distMia <= distRival) {
            estrategia = "AVANZAR A META";
            razonEstrategia = "Vas igual o mas cerca de tu meta (columna " + metaCol + "). Prioriza avanzar hacia " + dirMeta + ".";
        } else {
            estrategia = "AVANZAR A META";
            razonEstrategia = "El rival lleva ventaja. Avanza hacia " + dirMeta + " (columna " + metaCol + ") sin perder tiempo.";
        }

        // Calcular qué movimientos válidos reducen la distancia a meta (sin ambigüedad)
        List<String> acercanAMeta = new ArrayList<>();
        for (String ac : permitidos.isEmpty() ? validas : permitidos) {
            int nc = c;
            if (ac.equals("E")) nc++; if (ac.equals("O")) nc--;
            if (Math.abs(nc - metaCol) < distMia) acercanAMeta.add(ac);
        }

        StringBuilder sb = new StringBuilder();
        sb.append("Eres una moto de luz en Tron. N=arriba, S=abajo, E=derecha(col+1), O=izquierda(col-1).\n");
        sb.append("No puedes pisar muros(#), rastros(a/b) ni al rival. Ganas llegando a tu columna meta.\n\n");

        sb.append("MAPA (tu=").append(jugador).append(" rastro=").append(Character.toLowerCase(jugador));
        sb.append(", rival=").append(rival).append(" rastro=").append(Character.toLowerCase(rival)).append("):\n");
        sb.append(mapaVisual).append("\n");

        sb.append("TU: fila ").append(f).append(", col ").append(c);
        sb.append(" | META: col ").append(metaCol).append(" hacia ").append(dirMeta);
        sb.append(" | Distancia: ").append(distMia).append("\n");
        sb.append("RIVAL: fila ").append(rF).append(", col ").append(rC);
        sb.append(" | Distancia a su meta: ").append(distRival).append("\n\n");

        if (historial.size() > 1) {
            sb.append("HISTORIAL (antigua a reciente): ").append(String.join(" -> ", historial)).append("\n\n");
        }

        sb.append("ADYACENCIAS: ").append(adyacentes).append("\n");
        sb.append("SALIDAS: ").append(salidasInfo).append("\n");
        if (!callejones.isEmpty()) {
            sb.append("*** PROHIBIDO (callejon 0 salidas): ").append(callejones).append(" ***\n");
        }
        sb.append("PUEDES ELEGIR: ").append(permitidos.isEmpty() ? validas : permitidos).append("\n\n");

        if (!acercanAMeta.isEmpty()) {
            sb.append("MOVIMIENTOS QUE TE ACERCAN A TU META: ").append(acercanAMeta).append("\n");
        }
        sb.append("\n");
        sb.append("=== ESTRATEGIA DE ESTE TURNO: ").append(estrategia).append(" ===\n");
        sb.append(razonEstrategia).append("\n\n");

        sb.append("Razona en 2 lineas aplicando la estrategia indicada.\n");
        sb.append("Ultima linea OBLIGATORIAMENTE: ACCION: X  (X de: ");
        sb.append(permitidos.isEmpty() ? validas : permitidos).append(")");

        return sb.toString();
    }

    private String parsearRespuestaGroq(String jsonResponse) {
        // Groq devuelve "content":"... " o "content": "..."
        String token = "\"content\":\"";
        int start = jsonResponse.indexOf(token);
        if (start == -1) {
            token = "\"content\": \""; // Con espacio
            start = jsonResponse.indexOf(token);
        }

        if (start != -1) {
            start += token.length();
            int end = jsonResponse.indexOf("\"", start);
            if (end != -1) {
                String texto = jsonResponse.substring(start, end);
                return texto.replace("\\n", "\n").replace("\\\"", "\"");
            }
        }
        return jsonResponse;
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