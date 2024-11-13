#include <iostream>
#include <mpi.h>
#include <chrono>

#define N 5

void sequential_matrix_multiply(int a[N][N], int b[N][N], int c[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mpi_matrix_multiply(int* a, int* b, int* c, int n, int rank, int size) {
    int rows_per_process = n / size;
    int* sub_a = new int[rows_per_process * n];
    int* sub_c = new int[rows_per_process * n];

    MPI_Scatter(a, rows_per_process * n, MPI_INT, sub_a, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(b, n * n, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < n; j++) {
            sub_c[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                sub_c[i * n + j] += sub_a[i * n + k] * b[k * n + j];
            }
        }
    }

    MPI_Gather(sub_c, rows_per_process * n, MPI_INT, c, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    delete[] sub_a;
    delete[] sub_c;
}

void print_matrix(int* matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i * n + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[N][N], b[N][N], c[N][N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = rand() % 100 + 1;
                b[i][j] = rand() % 100 + 1;
            }
        }

        std::cout << "Розмірність матриць: " << N << "x" << N << std::endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    if (rank == 0) {
        sequential_matrix_multiply(a, b, c);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Послідовний метод: " << duration.count() << " секунд" << std::endl;

        std::cout << "Матриця A:" << std::endl;
        print_matrix(&a[0][0], N);
        std::cout << "Матриця B:" << std::endl;
        print_matrix(&b[0][0], N);
        std::cout << "Результат множення C:" << std::endl;
        print_matrix(&c[0][0], N);
    }

    start = std::chrono::high_resolution_clock::now();
    mpi_matrix_multiply(&a[0][0], &b[0][0], &c[0][0], N, rank, size);
    if (rank == 0) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Паралельний метод (MPI): " << duration.count() << " секунд" << std::endl;

        std::cout << "Результат множення C (паралельний метод):" << std::endl;
        print_matrix(&c[0][0], N);
    }

    MPI_Finalize();
    return 0;
}