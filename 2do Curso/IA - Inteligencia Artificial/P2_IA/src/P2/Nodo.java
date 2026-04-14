package P2;
import java.util.Objects;

class Nodo implements Comparable<Nodo> {
	
	int f, c;
	Nodo padre;
	String accion;
	int g;
	int h;
	int valorF;
	
 public Nodo(int f, int c, Nodo padre, String accion, int g, int h) {
	 
	 this.f = f;
	 this.c = c;
	 this.padre = padre;
	 this.accion = accion;
	 this.g = g;
	 this.h = h;
	 this.valorF = g + h;
 }
 
 @Override
 public int compareTo(Nodo otro) {
	 if(this.valorF != otro.valorF)
	 return Integer.compare(this.valorF, otro.valorF);
	 else
		 return Integer.compare(this.h, otro.h);
 }
 
 @Override
 public boolean equals(Object o) {
 if (this == o) return true;
 if (o == null || getClass() != o.getClass()) return false;
 Nodo nodo = (Nodo) o;
 return f == nodo.f && c == nodo.c;
 }
 
 @Override
 public int hashCode() {
 return Objects.hash(f, c);
 }
 
 @Override
 public String toString() {
 return "(" + f + "," + c + ")";
 }
}