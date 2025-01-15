#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono> // Para medir tiempos

void calculate_sum_with_reduction() {
    const int ROWS = 1000, COLS = 1000;
    std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS, 1)); // Matriz inicializada a 1
    long long sum = 0;

    // Iniciar el cronómetro
    auto start = std::chrono::high_resolution_clock::now();

    // Usar OpenMP con reducción para calcular la suma
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            sum += matrix[i][j];
        }
    }

    // Detener el cronómetro
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Resultado (con reduction): " << sum << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
}

int main() {
    calculate_sum_with_reduction();
    return 0;
}
