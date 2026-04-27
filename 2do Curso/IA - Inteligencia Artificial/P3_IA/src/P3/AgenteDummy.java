package P3;

/*
 * =====================================================
 * AGENTE DUMMY DE PRUEBA
 * =====================================================
 */
class AgenteDummy {
    public String resolver(Entorno mapa, char jugador) {
        String[] acciones = { "E", "N", "S", "O" };
        for (String accion : acciones) {
            int nf = mapa.getAgenteF(jugador);
            int nc = mapa.getAgenteC(jugador);
            if (accion.equals("N"))
                nf--;
            if (accion.equals("S"))
                nf++;
            if (accion.equals("E"))
                nc++;
            if (accion.equals("O"))
                nc--;

            if (mapa.esTransitable(nf, nc)) {
                return accion; // AcciÃ³n por defecto vÃ¡lida
            }
        }
        return "null"; // Si no encuentra ninguna, Game Over
    }
}