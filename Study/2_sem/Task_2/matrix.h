#include <iostream>
#ifndef MATRIX_H
#define MATRIX_H
class Matrix
{
    public:
    Matrix(int m = 0, int n = 0)
    {
        m_rows = m;
        n_cols = n;
        
        if ((n == 0) || (m == 0))
            values = nullptr;
        else
        {
            values = new double[m_rows*n_cols];
            for (int i = 0; i < m_rows*n_cols; ++i)
            {
                values[i] = 0;
            }
        }   
    }
    Matrix(const Matrix & M);
    Matrix(double const val);
    Matrix(const double * const arr, const int m);
    Matrix(const int n, const double * arr); 
    Matrix(const char * str); 

    static Matrix identity(const int n)
    {
        Matrix E;
        E.m_rows = n;
        E.n_cols = n;
        E.values = new double[n*n];
        
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < n; ++j) 
            {
                if (i == j) {
                    E.values[i*n + j] = 1;
                }
                else {
                    E.values[i*n + j] = 0;
                }
            }
        }
        return E;
    }

    static Matrix diagonal(const double * vals, const int n)
    {
        Matrix M;
        M.m_rows = n;
        M.n_cols = n;
        M.values = new double[n*n];

        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < n; ++j) 
            {
                if (i == j) {
                    M.values[i*n + j] = vals[i];
                }
                else {
                    M.values[i*n + j] = 0;
                }
            }
        }
        return M;
    }

    int rows() {return m_rows;}
    int columns() {return n_cols;}

    const Matrix get_row(const int i);
    const Matrix get_column(const int j);

    void set(const int i, const int j, const double val);

    friend std::ostream & operator << (std::ostream & out, const Matrix M);

    const Matrix & operator = (const Matrix M);

    Matrix operator [] (const int i);

    // double & operator [] (const int i)
    // {
    //     return values[i*(n_cols - 1) + j - 1];
    // }

    double & operator [] (const int i, const  int j)
    {
        if ((i < 1) || (i > m_rows + 1) || (j < 1) || (j > n_cols + 1))
            throw "Incorrect matrix indexing";

        return values[(i - 1)*n_cols + j - 1];
    }

    Matrix & gauss();
    Matrix & swap_max(const int i, const int j, double & del);
    // Matrix & swap(const int i, const int j, double & del);
    Matrix & subtract(const int i, const int j);
    // double determinant();

    double deteminant();
    Matrix solve();
    Matrix transposition();

    friend Matrix operator ~ (Matrix M);

    friend Matrix operator * (const Matrix M, const double c);
    friend Matrix operator + (const Matrix M1, const Matrix M2);
    friend Matrix operator - (const Matrix M1, const Matrix M2);
    friend Matrix operator * (const Matrix M1, const Matrix M2);
    Matrix operator - () const;            // унарный минус
    
    const Matrix & operator *= (const int c);
    const Matrix & operator += (const Matrix M);
    const Matrix & operator -= (const Matrix M);
    const Matrix & operator *= (const Matrix M);

    friend Matrix operator | (const Matrix M1, const Matrix M2);
    friend Matrix operator / (const Matrix M1, const Matrix M2);

    bool operator == (const Matrix M);
    bool operator != (const Matrix M);

    ~Matrix()
    {
        if(values != nullptr)
            delete[] values;
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    private:
        int m_rows;
        int n_cols;
        double *values;
        static double EPS;
};

#endif