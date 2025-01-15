#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono> // Para medir tiempos

// Función principal del microservicio
void calculate_sum_with_atomic() {
    const int ROWS = 1000, COLS = 1000;
    std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS, 1)); // Matriz inicializada a 1
    long long sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    // Paralelización con exclusión mutua usando atomic
    #pragma omp parallel for
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            #pragma omp critical
            sum += matrix[i][j];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Resultado (con atomic): " << sum << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
}

int main() {
    calculate_sum_with_atomic();
    return 0;
}

