package P2;

class Entorno {
	 char[][] grid;
	 int filas, cols;
	 int agenteF, agenteC;
	 int metaF, metaC;
	 public Entorno(String mapa) {
	 String[] lineas = mapa.trim().split("\n");
	 filas = lineas.length;
	 cols = lineas[0].length();
	 grid = new char[filas][cols];
	 for (int i = 0; i < filas; i++) {
	 for (int j = 0; j < cols; j++) {
	 char celda = lineas[i].charAt(j);
	 grid[i][j] = celda;
	// MODIFICACIÓN 1: Tratamos 'E' y 'A' como el inicio del agente
	 if (celda == 'E' || celda == 'A') { agenteF = i; agenteC = j; grid[i][j] = 'A';}
	 if (celda == 'S') { metaF = i; metaC = j; }
	 }
	 }
	 }
	 public boolean esTransitable(int f, int c) {
	     if (f < 0 || f >= filas || c < 0 || c >= cols) return false;
	     return grid[f][c] != '#' && grid[f][c] != '.';
	 }
	// MODIFICACIÓN 2: Nuevo método para evaluar nodos virtuales (usado por A*, BFS, DFS)
	 public boolean esMeta(int f, int c) {
	 return f == metaF && c == metaC;
	 }
	 public boolean moverAgente(String accion) {
	 int nf = agenteF, nc = agenteC;
	 if (accion.equalsIgnoreCase("N")) nf--;
	 if (accion.equalsIgnoreCase("S")) nf++;
	 if (accion.equalsIgnoreCase("E")) nc++;
	 if (accion.equalsIgnoreCase("O")) nc--;
	 if (!esTransitable(nf, nc)) return false;
	 grid[agenteF][agenteC] = '.'; // Deja rastro por donde pasa
	 agenteF = nf; agenteC = nc;

	 if (grid[nf][nc] != 'A') grid[nf][nc] = 'E'; // Pinta al agente
	 return true;
	 }
	 public boolean hemosGanado() {
	 return agenteF == metaF && agenteC == metaC;
	 }
	 public void dibujar() {
	 for (char[] fila : grid) {
	 System.out.println(new String(fila));
	 }
	 }
	}