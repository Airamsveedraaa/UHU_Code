package P2;
import java.util.Queue;
import java.util.PriorityQueue;
import java.util.List;
import java.util.LinkedList;


public class BusquedaAEstrella extends Busqueda{
		 private Queue<Nodo> Abiertos=new PriorityQueue<>();
		 private Queue<Nodo> Cerrados=new PriorityQueue<>();
		 
		 boolean propiaH=false;
		 
		 public BusquedaAEstrella(boolean usarH) {
			 this.propiaH=usarH; //constructor para que se decida que heurística usará el agente
		 }
		 
		 public int calcularH(int f, int c, Entorno mapa) {
			 
			 if(!propiaH) {
				 return Math.abs(f-mapa.metaF) + Math.abs(c-mapa.metaC);
			 }
			 else
			 {
				 int despF=mapa.metaF - f;
				 int despC=mapa.metaC - c; //desplazamientos del agente en ese instante
				return ((despF >= 0) ? despF : despF*(-2)) + ((despC >=0) ? despC : despC*(-2));
				//si despF es positivo nos indica que debemos ir hacia arriba para encontrar la salida, se penaliza ese movimiento de esa manera con despF*(-2)
				//haciendo que ese movimiento se elija menos, si es menor a 0 se deja despF tal cual, indica que debemos ir hacia abajo que no está penalizado.
				//misma lógica con despC para izquierda y derecha.
			 }
		 }
		 private Queue<Nodo> getSucesores(Nodo Actual, Entorno mapa){
				
			 Queue<Nodo> sucesores=new PriorityQueue<>(); //cola de sucesores a devolver
			 int f=Actual.f;
			 int c=Actual.c;
			 int g=Actual.g; //f c y g del nodo en ese momento
			 
			 if(mapa.esTransitable(f -1, c)) {
				 int h=calcularH(f,c,mapa); //heurística de Distancia Manhattan o distancia Manhattan Ponderada, depende del constructor que se haya utilizado
				 sucesores.add(new Nodo(f-1,c,Actual,"N",g+super.costeIZQ_ARRIBA,h));}
			 if(mapa.esTransitable(f+1, c)) {
				 int h=calcularH(f,c,mapa); //IDEM
				 sucesores.add(new Nodo(f+1,c,Actual,"S",g+super.costeDER_ABAJO,h));}
			 if(mapa.esTransitable(f, c+1)) {
				 int h=calcularH(f,c,mapa); //IDEM
				 sucesores.add(new Nodo(f,c+1,Actual,"E",g+super.costeDER_ABAJO,h));}
			 if(mapa.esTransitable(f, c-1)) {
				 int h=calcularH(f,c,mapa); //IDEM
				 sucesores.add(new Nodo(f,c-1,Actual,"O",g+super.costeIZQ_ARRIBA,h));}
			 return sucesores;
		 }
		 
		 private Queue<Nodo> quitarRepetidos(Queue<Nodo> sucesores, Queue<Nodo> Cerrados){
			
			 Queue<Nodo> noRepetidos=new PriorityQueue<>();
			 List<Nodo> temp=new LinkedList<>(sucesores); //para extrar un nodo de forma temporal para comparaciones
			 for(int i=0; i<temp.size(); i++) {
				 Nodo s=temp.get(i);
			 if(!Cerrados.contains(s)) {
				 //si no está en la cola de cerrados quiere decir que no es repetido, se añade
				 noRepetidos.add(s);
			 }
			 }
			 return noRepetidos;
		 }
		 
	 public List<String> resolver(Entorno mapa) {

		 Queue<Nodo> sucesores=new PriorityQueue<>();
		 int Hinicial=Math.abs(mapa.agenteF-mapa.metaF) + Math.abs(mapa.agenteC - mapa.metaC); //el nodo inicial también tiene h que hay que calcular
		 super.tIni=System.currentTimeMillis(); //para cálculo de tiempo de ejecución
		 Nodo inicial = new Nodo(mapa.agenteF,mapa.agenteC,null,null,0,Hinicial);
		 Abiertos.add(inicial);
		 int paso=1; //para indicar el número de paso en la traza
		 System.out.println("Iniciando busqueda A*...");
		 System.out.println(" Origen: " + "(" + inicial.f + "," + inicial.c + ")  -> Meta: " + "(" + mapa.metaF + "," + mapa.metaC + ")\n\n" );
		 while(Abiertos.size()>0) {
			 int tam=Abiertos.size();
			 if(tam > super.tamMax) super.tamMax=tam; //obtenemos de esta forma el máximo número de nodos que ha tenido abiertos en toda la ejecución
			 super.nAbiertos++; //para mostrar el numero de nodos expandidos en toda la ejecución.
			 Nodo Actual=Abiertos.remove();
			 Cerrados.add(Actual);
			 System.out.println("[PASO " + paso + " ]");
			 System.out.println("Seleccionado: " + Actual + " [f= " + Actual.valorF + ", g= " + Actual.g + ", h= " + Actual.h +" ]");
			 
			 if(mapa.esMeta(Actual.f, Actual.c)) {
				 //si hemos llegado a la meta, calculamos el tiempo de ejecución y reconstruimos el camino para mostrarlo.
				 super.tFin=System.currentTimeMillis();
				 super.tiempo=super.tFin-super.tIni;
				 return super.reconstruirCamino(Actual, "A*");
			 }
			 else {
				 //si aun no es meta, obtenemos los sucesores, tratamos los repetidos y volvemos a repetir el proceso
				 	sucesores=getSucesores(Actual,mapa);
				 	sucesores=quitarRepetidos(sucesores,Cerrados);
				 	Abiertos.addAll(sucesores);
				 	Actual=Abiertos.peek();
				}
			 	//importante, en cada pasada se muestra los sucesores y el estado de las estructuras
				System.out.println("Generados hijos: (" + sucesores + ")");
				System.out.println("Estado ABIERTOS: " + Abiertos);
				System.out.println("Estado CERRADOS: " + Cerrados);
				paso++;
		 }
		 //si no encuentra la solucion se calcula el tiempo de ejecucion y se muestra el mensaje correspondiente.
		 super.tFin=System.currentTimeMillis();
		 super.tiempo=super.tFin-super.tIni;
		 System.out.println("Solución no encontrada usando A*");
		 System.out.println("Nodos Expandidos: " + super.nAbiertos);
		 System.out.println("Tiempo de ejecucion: " + super.tiempo + "ms\n");
	 return null;
	 }
}




