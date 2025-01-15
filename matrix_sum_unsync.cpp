#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono> // Para medir tiempos
#include "benchmark.h"

void calculate_sum() {
    systemMetrics sm("Prueba");
        sm.resetCounters();
    const int ROWS = 1000, COLS = 1000;
    std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS, 1)); // Matriz inicializada en 1
    long long sum = 0;

    // Iniciar el cronómetro
    auto start = std::chrono::high_resolution_clock::now();

    // Paralelización sin sincronización
    #pragma omp parallel for
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            sum += matrix[i][j]; // Condición de carrera
        }
    }

    // Detener el cronómetro
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Resultado (sin sincronización): " << sum << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
    sm.calculate();
    sm.printMetrics();
}

int main() {
    calculate_sum();
    return 0;
}

