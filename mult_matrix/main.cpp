#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "mult.cpp"

#define m 512
#define n 1024
#define k 512

template <typename T>
void
print_matrix(const std::vector<std::vector<T>> & M)
{
    for(const auto & row : M) 
    {
        for (auto value : row) 
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
std::vector<std::vector<T>> 
set_matrix_A(int rows = n, int cols = m) 
{
    std::vector<std::vector<T>> A(rows, std::vector<T>(cols));
    
    std::random_device rnd_device;
    std::mt19937 gen_engine {rnd_device()};
    std::uniform_real_distribution<T> dist {0.0, 1.0};
    
    auto gen = [&](){
                   return dist(gen_engine);
               };

    for (auto & row : A) 
    {
        std::generate(row.begin(), row.end(), gen);
    }

    return A;
}

template <typename T>
std::vector<std::vector<T>> 
set_matrix_B(int rows = m, int cols = k) 
{
    std::vector<std::vector<T>> B(rows, std::vector<T>(cols));

    std::random_device rnd_device;
    std::mt19937 gen_engine {rnd_device()};
    std::uniform_real_distribution<T> dist {0.0, 1.0};
    
    auto gen = [&](){
                   return dist(gen_engine);
               };

    for (auto & row : B) 
    {
        std::generate(row.begin(), row.end(), gen);
    }

    return B;
}

int
main()
{
    auto A = set_matrix_A<double>();
    auto B = set_matrix_B<double>();

    // print_matrix<float>(A);
    // print_matrix<float>(B);

    // auto C_1 = multiply<float>(A, B);
    // auto C_2 = multiply_parallel<float>(A, B, 2);
    std::vector<int> num_threads{2, 4, 6, 8};

    

    for(int i = 0; i < int(num_threads.size()); ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        auto C = multiply_parallel<double>(A, B, num_threads[i]);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "Execution time: " << elapsed.count() << ". Threads num: " 
            << num_threads[i] << "." << std::endl;
    }
}
