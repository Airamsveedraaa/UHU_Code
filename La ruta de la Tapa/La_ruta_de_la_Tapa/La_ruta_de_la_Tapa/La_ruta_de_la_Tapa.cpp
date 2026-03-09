#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura para representar un bar
struct Bar {
    string nombre;
    int valoracion;
    int tiempoConsumicion;
    int tiempoDesplazamiento;

    int tiempoTotal() const {
        return 2 * tiempoDesplazamiento + tiempoConsumicion;
    }

    double ratio() const {
        return static_cast<double>(valoracion) / tiempoTotal();
    }
};

// Función genérica para ejecutar una estrategia
vector<Bar> ejecutarEstrategia(vector<Bar> bares, int tiempoDisponible, int estrategia, int& valoracionTotalOut) {
    switch (estrategia) {
    case 1: // Valoración descendente
        sort(bares.begin(), bares.end(), [](const Bar& a, const Bar& b) {
            return a.valoracion > b.valoracion;
            });
        break;
    case 2: // Tiempo total ascendente
        sort(bares.begin(), bares.end(), [](const Bar& a, const Bar& b) {
            return a.tiempoTotal() < b.tiempoTotal();
            });
        break;
    case 3: // Ratio descendente
        sort(bares.begin(), bares.end(), [](const Bar& a, const Bar& b) {
            return a.ratio() > b.ratio();
            });
        break;
    default:
        cout << "Estrategia inválida.\n";
        return {};
    }

    vector<Bar> seleccionados;
    int tiempoRestante = tiempoDisponible;
    valoracionTotalOut = 0;

    for (const Bar& bar : bares) {
        int t = bar.tiempoTotal();
        if (tiempoRestante >= t) {
            seleccionados.push_back(bar);
            tiempoRestante -= t;
            valoracionTotalOut += bar.valoracion;
        }
    }

    return seleccionados;
}

// Muestra los resultados en formato limpio
void mostrarResultados(const vector<Bar>& bares, int tiempoDisponible, int estrategia, int valoracionTotal) {
    string nombreEstrategia;
    switch (estrategia) {
    case 1: nombreEstrategia = "Ordenar por valoracion (de mayor a menor)"; break;
    case 2: nombreEstrategia = "Ordenar por tiempo total (de menor a mayor)"; break;
    case 3: nombreEstrategia = "Ordenar por ratio valoracion/tiempo (de mayor a menor)"; break;
    }

    cout << "\nESTRATEGIA " << estrategia << ": " << nombreEstrategia << "\n";
    cout << string(60, '=') << "\n";

    int tiempoTotalUsado = 0;
    for (size_t i = 0; i < bares.size(); ++i) {
        const Bar& b = bares[i];
        int t = b.tiempoTotal();
        cout << i + 1 << ". " << b.nombre
            << " (Valoracion: " << b.valoracion
            << ", Tiempo total: " << t << " min)\n";
        tiempoTotalUsado += t;
    }

    cout << "\nValoracion total conseguida: " << valoracionTotal << " puntos\n";
    cout << "Tiempo total empleado: " << tiempoTotalUsado << " minutos\n";
    cout << "Tiempo restante: " << tiempoDisponible - tiempoTotalUsado << " minutos\n";
    cout << string(60, '=') << "\n";
}

int main() {
    vector<Bar> bares = {
        {"El Rincon del Choco", 9, 30, 10},
        {"Bar La Esquina", 6, 15, 5},
        {"Tapas & Canas", 4, 15, 5},
        {"Casa Manolo", 8, 25, 5},
        {"La Bodeguita", 7, 20, 7},
        {"El Mirador", 10, 30, 12},
        {"Meson del Puerto", 5, 15, 5},
        {"La Taberna Asturiana", 8, 20, 10},
        {"El Rincon del Abuelo", 3, 25, 12},
        {"Taperia Central", 6, 20, 7}
    };

    const int tiempoDisponible = 180;
    cout << "=== RUTA DE LAS TAPAS - ALGORITMO VORAZ ===\n";
    cout << "Tiempo disponible: " << tiempoDisponible << " minutos (3 horas)\n";

    vector<Bar> res1, res2, res3;
    int val1, val2, val3;

    res1 = ejecutarEstrategia(bares, tiempoDisponible, 1, val1);

    res2 = ejecutarEstrategia(bares, tiempoDisponible, 2, val2);

    res3 = ejecutarEstrategia(bares, tiempoDisponible, 3, val3);

    // Elegir estrategia
    int opcion;
    cout << "\nCual estrategia deseas utilizar? (1, 2 o 3): ";
    cin >> opcion;

    switch (opcion) {
    case 1: mostrarResultados(res1, tiempoDisponible, 1, val1); break;
    case 2: mostrarResultados(res2, tiempoDisponible, 2, val2); break;
    case 3: mostrarResultados(res3, tiempoDisponible, 3, val3); break;
    default: cout << "Opción inválida.\n"; break;
    }

    return 0;
}
