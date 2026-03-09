#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

struct Serie {
    string titulo;
    int episodios;
    int duracion; // duración por episodio en minutos
    int valoracion;
    string genero;
};

struct Capitulo {
    Serie serie;
    int numero_episodio;
    int duracion;
    int valoracion;
};

// Función para imprimir los resultados
void imprimirResultados(const vector<Serie>& seriesSeleccionadas, int tiempoTotal, int valoracionTotal) {
    cout << "Series seleccionadas:\n";
    map<string, int> capitulosPorGenero;

    for (const auto& serie : seriesSeleccionadas) {
        cout << "- " << serie.titulo << ": " << serie.episodios << " capitulos\n";
        capitulosPorGenero[serie.genero] += serie.episodios;
    }

    cout << "\nValoracion total conseguida: " << valoracionTotal << " puntos\n";
    cout << "Tiempo total empleado: " << tiempoTotal << " minutos\n";
    cout << "Capitulos por genero:\n";

    for (const auto& genero : capitulosPorGenero) {
        cout << "- " << genero.first << ": " << genero.second << " capitulos\n";
    }
}

// Función principal del algoritmo
vector<Serie> maratonSeries(vector<Serie> series, int tiempoDisponible, int estrategia) {
    // Crear lista de todos los capítulos individuales
    vector<Capitulo> capitulos;

    for (const auto& serie : series) {
        for (int e = 1; e <= serie.episodios; e++) {
            capitulos.push_back({ serie, e, serie.duracion, serie.valoracion });
        }
    }

    // Ordenar capítulos según la estrategia seleccionada
    switch (estrategia) {
    case 1: // Ordenar por valoración (mayor a menor)
        sort(capitulos.begin(), capitulos.end(), [](const Capitulo& a, const Capitulo& b) {
            if (a.valoracion == b.valoracion) {
                return a.duracion < b.duracion; // Si misma valoración, menor duración primero
            }
            return a.valoracion > b.valoracion;
            });
        break;

    case 2: // Ordenar por duración (menor a mayor)
        sort(capitulos.begin(), capitulos.end(), [](const Capitulo& a, const Capitulo& b) {
            if (a.duracion == b.duracion) {
                return a.valoracion > b.valoracion; // Si misma duración, mayor valoración primero
            }
            return a.duracion < b.duracion;
            });
        break;

    case 3: // Ordenar por ratio valoración/duración (mayor a menor)
        sort(capitulos.begin(), capitulos.end(), [](const Capitulo& a, const Capitulo& b) {
            double ratioA = static_cast<double>(a.valoracion) / a.duracion;
            double ratioB = static_cast<double>(b.valoracion) / b.duracion;
            if (ratioA == ratioB) {
                return a.duracion < b.duracion; // Si mismo ratio, menor duración primero
            }
            return ratioA > ratioB;
            });
        break;
    }

    int tiempoRestante = tiempoDisponible;
    vector<Capitulo> capitulosSeleccionados;

    // Seleccionar capítulos según el orden y el tiempo disponible
    for (const auto& cap : capitulos) {
        if (tiempoRestante >= cap.duracion) {
            capitulosSeleccionados.push_back(cap);
            tiempoRestante -= cap.duracion;
        }
    }

    // Agrupar los capítulos seleccionados por serie
    map<string, Serie> seriesMap;
    for (const auto& serie : series) {
        seriesMap[serie.titulo] = { serie.titulo, 0, serie.duracion, serie.valoracion, serie.genero };
    }

    for (const auto& cap : capitulosSeleccionados) {
        seriesMap[cap.serie.titulo].episodios++;
    }

    vector<Serie> seriesSeleccionadas;
    int valoracionTotal = 0;
    int tiempoTotal = 0;

    for (const auto& pair : seriesMap) {
        if (pair.second.episodios > 0) {
            seriesSeleccionadas.push_back(pair.second);
            valoracionTotal += pair.second.valoracion * pair.second.episodios;
            tiempoTotal += pair.second.duracion * pair.second.episodios;
        }
    }

    cout << "\nESTRATEGIA " << estrategia << ": ";
    switch (estrategia) {
    case 1: cout << "Ordenar por valoracion (de mayor a menor)\n"; break;
    case 2: cout << "Ordenar por duracion (de menor a mayor)\n"; break;
    case 3: cout << "Ordenar por ratio valoracion/duracion (de mayor a menor)\n"; break;
    }
    cout << "---\n";

    imprimirResultados(seriesSeleccionadas, tiempoTotal, valoracionTotal);

    return seriesSeleccionadas;
}

int main() {
    // Datos de las series
    vector<Serie> series = {
        {"Stranger Things", 3, 50, 8, "ciencia-ficcion"},
        {"Breaking Bad", 2, 45, 9, "drama"},
        {"The Office", 5, 22, 7, "comedia"},
        {"Game of Thrones", 2, 60, 9, "fantasia"},
        {"Brooklyn Nine-Nine", 4, 22, 6, "comedia"},
        {"The Mandalorian", 2, 40, 8, "ciencia-ficcion"},
        {"Peaky Blinders", 3, 55, 7, "drama"},
        {"The Witcher", 2, 60, 7, "fantasia"},
        {"Money Heist", 3, 45, 8, "accion"},
        {"The Boys", 2, 55, 8, "accion"}
    };

    int tiempoDisponible = 600; // 10 horas en minutos
    int estrategia;

    cout << "=== MARATON DE SERIES ===\n";
    cout << "Tiempo disponible: " << tiempoDisponible << " minutos\n";
    cout << "Seleccione la estrategia:\n";
    cout << "1. Ordenar por valoracion (de mayor a menor)\n";
    cout << "2. Ordenar por duracion (de menor a mayor)\n";
    cout << "3. Ordenar por ratio valoracion/duracion (de mayor a menor)\n";
    cout << "Opcion: ";
    cin >> estrategia;

    if (estrategia < 1 || estrategia > 3) {
        cout << "Estrategia invalida. Por favor, elija una opcion entre 1 y 3.\n";
        return 1;
    }

    // Ejecutar solo la estrategia elegida
    maratonSeries(series, tiempoDisponible, estrategia);

    return 0;
}
