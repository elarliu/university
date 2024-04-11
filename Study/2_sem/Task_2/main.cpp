#include "matrix.h"
#include <iostream>

double Matrix::EPS = 0.0001;

int
main()
{
    // matrix( int n, int m ) 
    Matrix m1(3,3);
    std::cout << m1 << std::endl;

    // static matrix matrix::identity( int n )
    Matrix m2 = Matrix::identity(3);
    std::cout << m2 << std::endl;

    // static matrix matrix::diagonal( double* vals, int n )
    double arr[] = {1, 2, 3, 4};
    Matrix m3 = Matrix::diagonal(arr, 4);
    std::cout << m3 << std::endl;

    // matrix::set( int i, int j, double val ) 
    m1.set(2, 3, 2.3);
    std::cout << m1 << std::endl;
    
    // int matrix::rows()
    std::cout << "m3 rows:" << m3.rows() << std::endl;
    // int matrix::columns()
    std::cout << "m3 columns:" << m3.columns() << std::endl;

    // matrix * scalar
    Matrix m4 = m3 * 2;
    std::cout << m4 << std::endl;
    std::cout << m3 << std::endl;

    // matrix *= scalar
    m3 *= 4;
    std::cout << m3 << std::endl;

    // matrix( double )
    Matrix m5(5.0);
    std::cout << m5 << std::endl;

    // matrix( double*, int m )
    Matrix m6(arr, 4);
    std::cout << m6 << std::endl;

    // matrix( int n, double* ) 
    Matrix m7(4, arr);
    std::cout << m7 << std::endl;

    // matrix( char * )
    Matrix m8("{{1.5},{11}}");
    std::cout << m8 << std::endl;

    // Matrix m7 = m8;
    // -m8;

    // std::cout << m8 << std::endl;

    // matrix == matrix
    std::cout << (m7 == m7) << std::endl;
    
    // matrix != matrix
    std::cout << (m7 != m7) << std::endl;

    Matrix m11(3,4);
    std::cout << m11 << std::endl;

    m11.set(1, 4, 2.5);
    m11.set(2, 4, 2.5);
    m11.set(3, 4, 2.5);

    std::cout << m11 << std::endl;

    // matrix matrix::matrix[ i ]
    Matrix m9 = m3[3];
    std::cout << m9 << std::endl;

    // matrix matrix::matrix[ j ]
    Matrix m10 = m7[3];
    std::cout << m10 << std::endl;

    Matrix m12 = m11[4];
    std::cout << m12 << std::endl;

    Matrix m13(3,4);

    m13.set(1, 3, 1.5);
    m13.set(2, 3, 1.5);
    m13.set(3, 3, 1.5);
    m13.set(1, 1, 1);
    std::cout << m13 << std::endl;
    std::cout << m11 << std::endl;

    // correct test (without mismatching)
    Matrix m14 = Matrix::identity(3);

    try
    {
            // matrix + matrix
        std::cout << (m11 + m13 + m11) << std::endl;

        // - matrix
        m13 = -m13;
        std::cout << m13 << std::endl;
        m13 = -m13;

        // matrix - matrix
        std::cout << (m11 - m13) << std::endl;

        // matrix += matrix
        m13 += m11;
        std::cout << m13 << std::endl;

        // matrix -= matrix
        m13 -= m11;
        std::cout << m13 << std::endl;

        std::cout << m14 << std::endl;

        // matrix * matrix
        std::cout << (m14*(m14*2)) << std::endl;

        // matrix *= matrix
        m14 = m14*(m14*2);
        std::cout << m14 << std::endl;

        // несовсместимые матрицы
        Matrix m18(2,2);
        Matrix m19(3,3);

        Matrix m20 = m19*m18;
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
    
    Matrix m15(3,3);
    Matrix m16(3,4);
    Matrix m17(4,3);
    
    // matrix | matrix 
    std::cout << (m14 | m15) << std::endl;

    // matrix / matrix 
    std::cout << (m14 / m15) << std::endl;

    std::cout << (m14 | m16) << std::endl;
    std::cout << (m14 / m17) << std::endl;

    double arr1[] = {1, 2, 3};
    Matrix m21 = Matrix::diagonal(arr1, 3);
    std::cout << m21 << std::endl;

    m21[1, 1] = 5;
    // m21[2, 1] = 1;

    try
    {
        m21[1000, 1000] = 1000;
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
    

    std::cout << m21 << std::endl;

    Matrix b("{{1},{1},{1}}");
    
    std::cout << "Determinant: " << m21.deteminant() << std::endl;

    std::cout << m21 << std::endl;

    Matrix A = m21|b;

    std::cout << "Solving: " << std::endl << A << std::endl;

    try
    {
        Matrix x = (m21|b).solve();
        std::cout << "Solution: " << std::endl << x << std::endl;
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }

    Matrix m22(3,3);
    m22[1,2] = 1;
    m22[1,3] = 2;
    m22[2,1] = 3;
    m22[2,3] = 4;
    m22[3,1] = 5;
    m22[3,2] = 6;
    std::cout << m22 << std::endl;
    std::cout << m22.transposition() << std::endl;
    std::cout << m22 << std::endl;

    m2[2,2] = 5;
    
};