#include <vector>
#include <iostream>
#include <omp.h> 
#ifndef MULT_HPP
#define MULT_HPP

template <typename T>
std::vector<std::vector<T>> 
multiply_parallel(
    const std::vector<std::vector<T>> & A, 
    const std::vector<std::vector<T>> & B,
    int num_threads);

template <typename T>
std::vector<std::vector<T>> 
multiply(
    const std::vector<std::vector<T>> & A, 
    const std::vector<std::vector<T>> & B);
    
#endif