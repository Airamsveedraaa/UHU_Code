package P0;

 interface MetricaManhatan {//greedy
	int distManhatan (int f,int c, Entorno mapa);
}

interface MetricaHuecos{//Deliberativo2A
	int numHuecos(int f, int c, Entorno mapa);
}

interface MetricaPasos{//Deliberativo2B
	int numPasos (int f,int c,int df, int dc, char mem[][], Entorno mapa);

}

interface MetricaMem{//Deliberativo2B
	void actualizarMem(int f,int c, Entorno mapa);
}

interface MetricaInercia{//Deliberativo2B
	boolean puedeInercia(String ultimaAccion, int f, int c, char mem[][],Entorno mapa);
}


interface MetricaSalida{//Deliberativo2A
	boolean esSalida(int f,int c, Entorno mapa);
}

