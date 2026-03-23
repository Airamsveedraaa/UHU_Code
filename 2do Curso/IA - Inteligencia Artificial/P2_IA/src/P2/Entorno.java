package P2;

//==========================================
//CLASE ENTORNO (Lógica del Juego)
//==========================================
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
             grid[i][j] = lineas[i].charAt(j);
             if (grid[i][j] == 'A') { agenteF = i; agenteC = j; }
             if (grid[i][j] == 'S') { metaF = i; metaC = j; }
         }
     }
 }

 public boolean esTransitable(int f, int c) {
     if (f < 0 || f >= filas || c < 0 || c >= cols) return false;
     return grid[f][c] != '#' && grid[f][c] != '.';
 }
 
 public char verCasilla(int f, int c) {
     if (f < 0 || f >= filas || c < 0 || c >= cols) return '#';
     return grid[f][c];
 }

 public boolean hemosGanado() { return agenteF == metaF && agenteC == metaC; }

 public boolean moverAgente(String accion) {
     int nf = agenteF, nc = agenteC;
     if (accion.equalsIgnoreCase("N")) nf--;
     if (accion.equalsIgnoreCase("S")) nf++;
     if (accion.equalsIgnoreCase("E")) nc++;
     if (accion.equalsIgnoreCase("O")) nc--;

     if (!esTransitable(nf, nc)) return false;

     grid[agenteF][agenteC] = '.'; // Deja rastro
     agenteF = nf; agenteC = nc;
     
     if (grid[nf][nc] != 'S') grid[nf][nc] = 'A';
     return true;
 }

 public void dibujar() {
     for (char[] fila : grid) System.out.println(new String(fila));
 }
}