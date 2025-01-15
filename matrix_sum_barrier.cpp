#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono> // Para medir tiempos

void calculate_sum_with_barrier() {
    const int ROWS = 1000, COLS = 1000;
    std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS, 1)); // Matriz inicializada a 1
    std::vector<long long> row_sums(ROWS, 0);
    long long total_sum = 0;

    // Iniciar el cronómetro
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        // Fase 1: Suma por filas
        #pragma omp for
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                row_sums[i] += matrix[i][j];
            }
        }

        // Barrera para sincronizar la suma de filas antes de calcular la suma total
        #pragma omp barrier

        // Fase 2: Suma total (realizada por un solo hilo)
        #pragma omp single
        {
            for (int i = 0; i < ROWS; ++i) {
                total_sum += row_sums[i];
            }
        }
    }

    // Detener el cronómetro
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Resultado (con barrier): " << total_sum << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
}

int main() {
    calculate_sum_with_barrier();
    return 0;
}
