#include <vector>
#include <iostream>
#include <omp.h> 
#include "mult.hpp"

template <typename T>
std::vector<std::vector<T>> 
multiply_parallel(
    const std::vector<std::vector<T>> & A, 
    const std::vector<std::vector<T>> & B,
    int num_threads)
{
    int n = A.size();                   // количество строк в A
    int m = B[0].size();                // количество столбцов в B
    int p = B.size();                   // количество строк в B
    std::vector<std::vector<T>> C(n, std::vector<T>(m));

    omp_set_num_threads(num_threads);

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            for (int k = 0; k < p; ++k) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

template <typename T>
std::vector<std::vector<T>> 
multiply(
    const std::vector<std::vector<T>> & A, 
    const std::vector<std::vector<T>> & B)
{
    int n = A.size();                   // количество строк в A
    int m = B[0].size();                // количество столбцов в B
    int p = B.size();                   // количество строк в B
    std::vector<std::vector<T>> C(n, std::vector<T>(m));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            for (int k = 0; k < p; ++k) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}