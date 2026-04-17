#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

// Estados
const int SUSCEPTIBLE = 0;
const int INFECTADO = 1;
const int RECUPERADO = 2;

// Tamaño de la grilla
const int N = 50;

// Días de simulación
const int DIAS = 365;

// Probabilidades
const double P_INFECCION = 0.25;
const double P_RECUPERACION = 0.05;

// Número aleatorio entre 0 y 1
double random_prob() {
    return (double) rand() / RAND_MAX;
}

// Inicializar grilla
void inicializar(vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = SUSCEPTIBLE;
        }
    }

    // Paciente cero
    grid[N/2][N/2] = INFECTADO;
}

// Contar infectados
int contar_infectados(const vector<vector<int>>& grid) {
    int total = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == INFECTADO)
                total++;
        }
    }
    return total;
}

int main() {
    srand(time(0));

    vector<vector<int>> grid(N, vector<int>(N));
    vector<vector<int>> new_grid(N, vector<int>(N));

    inicializar(grid);

    // 📁 Crear archivo CSV
    ofstream archivo("resultados.csv");
    archivo << "dia,infectados\n";

    // ⏱ Medir tiempo
    auto inicio = chrono::high_resolution_clock::now();

    for (int dia = 0; dia < DIAS; dia++) {

        new_grid = grid;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                if (grid[i][j] == INFECTADO) {

                    int dx[4] = {-1, 1, 0, 0};
                    int dy[4] = {0, 0, -1, 1};

                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];

                        if (ni >= 0 && ni < N && nj >= 0 && nj < N) {
                            if (grid[ni][nj] == SUSCEPTIBLE) {
                                if (random_prob() < P_INFECCION) {
                                    new_grid[ni][nj] = INFECTADO;
                                }
                            }
                        }
                    }

                    // recuperación
                    if (random_prob() < P_RECUPERACION) {
                        new_grid[i][j] = RECUPERADO;
                    }
                }
            }
        }

        grid = new_grid;

        int infectados = contar_infectados(grid);

        // Guardar en CSV
        archivo << dia << "," << infectados << "\n";

        // Mostrar en pantalla
        cout << "Dia " << dia << " - Infectados: " << infectados << endl;
    }

    // ⏱ Fin del tiempo
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "\nTiempo total: " << duracion.count() << " segundos\n";

    archivo.close();

    return 0;
}