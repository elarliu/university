#include "matrix.h"
#include <cstring>
#include <cmath>

Matrix::Matrix(const double val)
{
    m_rows = 1;
    n_cols = 1;
    values = new double[1];
    values[0] = val;   
}

Matrix::Matrix(const double * arr, const int m)
{
    if ((m == 0) || (arr == nullptr))
    {
        m_rows = 0;
        n_cols = 0;
        values = nullptr;
    }
    else
    {
        m_rows = 1;
        n_cols = m;
        values = new double[n_cols];
        for (int i = 0; i < n_cols; ++i)
        {
            values[i] = arr[i];
        }
    }
    
}

Matrix::Matrix(const int n, const double * arr)
{
    if((n == 0) || (arr == nullptr))
    {
        m_rows = 0;
        n_cols = 0;
        values = nullptr;
    }
    else
    {
        m_rows = n;
        n_cols = 1;
        values = new double[m_rows];
        for (int i = 0; i < m_rows; ++i)
        {
            values[i] = arr[i];
        }
    }
    
}

Matrix::Matrix(const char * str)
{
    if (str == nullptr)
    {
        m_rows = 0;
        n_cols = 0;
        values = nullptr;
    }
    else
    {
        int brct = 0;
        int cntrl = 0;
        int commas = 0;
        int flg = 1;
        for (int i = 0; (i < strlen(str)) && flg; ++i)
        {
            // std::cout << "aboba" << std::endl;
            if(cntrl < 0)
            {
                flg = 0;
            }
            else if (str[i] == '{')
            {
                ++cntrl;
            }
            else if (str[i] == '}')
            {
                --cntrl;
                ++brct;
            }
            else if (str[i] == ',')
                ++commas;
        }
        // std::cout << "Brackets: " << brct << std::endl;
        // std::cout << "Commas: " << commas << std::endl;
        // std::cout << "Cntrl: " << cntrl << std::endl;
        if (cntrl != 0)
            flg = 0;
        // std::cout << "Flag: " << flg << std::endl;
        if (flg)
        {
            if (brct == 1)
            {
                m_rows = 1;
                n_cols = commas + 1;
                values = new double[n_cols];
            }
            else
            {
                m_rows = brct - 1;
                n_cols = (commas - brct + 2)/(brct - 1) + 1;
                values = new double[n_cols*m_rows];
            }
            int i = 0;
                char number[10];
                int num_ind = 0;
                double data;
                for (int j = 0; j < strlen(str) - 1; ++j)
                {
                    if (('0' <= str[j]) && (str[j] <= '9') || str[j] == '.')
                    {
                        number[num_ind] = str[j];
                        ++num_ind;
                        if(str[j + 1] == '}' || str[j + 1] == ',')
                        {
                            number[num_ind] = '\0';
                            data = atof(number);
                            values[i] = data;
                            ++i;
                            num_ind = 0;
                        }
                    }
                }
        }
        else
        {
            m_rows = 0;
            n_cols = 0;
            values = nullptr;
            std::cout << "Incorrect matrix respresentation as a string" << std::endl;
        }
    }
}

Matrix::Matrix(const Matrix & M)
{
    m_rows = M.m_rows;
    n_cols = M.n_cols;
    values = new double[n_cols*m_rows];
    for (int i = 0; i < n_cols*m_rows; ++i)
    {
        values[i] = M.values[i];
    }
    
}

void 
Matrix::set(const int i, const int j, const double val)
{
    values[(i - 1)*n_cols + j - 1] = val;
}

std::ostream & operator << (std::ostream & out, const Matrix M)
{
    if (M.m_rows == 0)
    {
        std::cout << "Matrix is not initialised" << std::endl;
        return out;
    }

    for (int i = 0; i < M.m_rows; ++i)
    {
        for (int j = 0; j < M.n_cols; ++j)
            std::cout << M.values[i*M.n_cols + j] << " ";
        std::cout << std::endl;
        
    }

    return out;
}

const Matrix Matrix::get_row(const int i)
{
    Matrix row(1, n_cols);

    for (int j = 0; j < n_cols; ++j)
    {
        row.values[j] = values[(i - 1)*n_cols + j];
    }
    
    return row;
}

const Matrix Matrix::get_column(const int j)
{
    Matrix column(m_rows, 1);
    for (int i = 0; i < m_rows; ++i)
    {
        column.values[i] = values[i*n_cols + j - 1];
    }
    
    return column;
}

Matrix Matrix::operator [] (const int i)
{
    if (i <= m_rows)
        return get_row(i);
    else if (i <= n_cols)
        return get_column(i);
    else
    {
        throw "Error in matrix structure";
        // return Matrix();
    }

}

const Matrix & Matrix::operator += (const Matrix M)            // нужна обработка исключений
{
    if((n_cols != M.n_cols) || (m_rows != M.m_rows))
        throw "Matrix size's are mismatched";

    for (int i = 0; i < n_cols*m_rows; i++)
    {
        values[i] = values[i] + M.values[i];
    }

    return *this;
}

const Matrix & Matrix::operator -= (const Matrix M)            // нужна обработка исключений
{
    if((n_cols != M.n_cols) || (m_rows != M.m_rows))
        throw "Matrix size's are mismatched";

    for (int i = 0; i < n_cols*m_rows; i++)
    {
        values[i] = values[i] - M.values[i];
    }

    return *this;
}

const Matrix & Matrix::operator *= (const int c)
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            values[i*n_cols + j] *= c;
        }
    }
    return *this;
}

const Matrix & Matrix::operator *= (const Matrix M)
{
    if (n_cols != M.m_rows)
        throw "Matrix size's are mismatched";

    Matrix res(m_rows, M.n_cols);
    double sum = 0;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < M.n_cols; j++)
        {
            sum = 0;
            for (int k = 0; k < n_cols; k++)
                sum+= values[i*n_cols + k]*M.values[k*M.n_cols + j];
            res.values[i*res.n_cols + j] = sum;
        }
    }
    *this = res;
    return *this;
}

Matrix operator - (const Matrix M1, const Matrix M2)            // нужна обработка исключений
{
    if((M1.n_cols != M2.n_cols) || (M1.m_rows != M2.m_rows))
        throw "Matrix size's are mismatched";

    Matrix res(M1.m_rows, M1.n_cols);

    for (int i = 0; i < M1.n_cols*M1.m_rows; ++i)
    {
        res.values[i] = (M1.values[i] - M2.values[i]);
        // std::cout << "M1.value[i]: " << M1.values[i] << " M2.value[i]: " << M2.values[i] << std::endl;
        
    }

    return res;
}

Matrix operator + (const Matrix M1, const Matrix M2)            // нужна обработка исключений
{
    if((M1.n_cols != M2.n_cols) || (M1.m_rows != M2.m_rows))
        throw "Matrix size's are mismatched";
    
    Matrix res(M1.m_rows, M1.n_cols);

    for (int i = 0; i < M1.n_cols*M1.m_rows; i++)
    {
        res.values[i] = M1.values[i] + M2.values[i];
    }

    return res;
    
}

Matrix operator * (const Matrix M1, const Matrix M2)
{
    if (M1.n_cols != M2.m_rows)
        throw "Matrix size's are mismatched";

    Matrix res(M1.m_rows, M2.n_cols);
    double sum = 0;

    for (int i = 0; i < M1.m_rows; i++)
    {
        for (int j = 0; j < M2.n_cols; j++)
        {
            sum = 0;
            for (int k = 0; k < M1.n_cols; k++)
                sum+= M1.values[i*M1.n_cols + k]*M2.values[k*M2.n_cols + j];
            res.values[i*res.n_cols + j] = sum;
        }
    }
    return res;
}

Matrix operator * (const Matrix M, const double c)
{
    Matrix res(M.m_rows, M.n_cols);

    for (int i = 0; i < res.m_rows; i++)
    {
        for (int j = 0; j < res.n_cols; j++)
        {
            res.values[i*res.n_cols + j] = M.values[i*res.n_cols + j]*c;
        }
    }
    return res;
}

Matrix Matrix::operator - () const
{   
    Matrix res(m_rows, n_cols);

    for (int i = 0; i < n_cols*m_rows; ++i)
    {
        res.values[i] = -(values[i]);
    }

    return res;
}

bool Matrix::operator == (const Matrix M)
{

    if(n_cols != M.n_cols)
        return false;

    if(m_rows != M.m_rows)
        return false;

    for (int i = 0; i < n_cols*m_rows; ++i)
    {
        if(!(fabs(values[i] - M.values[i]) <= EPS))
            return false;
    }
    return true;
}

bool Matrix::operator != (const Matrix M)
{
    return !(*this == M);
}

const Matrix & Matrix::operator = (const Matrix M)
{
    delete[] values;

    m_rows = M.m_rows;
    n_cols = M.n_cols;
    values = new double[n_cols*m_rows];

    for (int i = 0; i < n_cols*m_rows; ++i)
    {
        values[i] = M.values[i];
    }

    return *this;
    
}

Matrix operator | (const Matrix M1, const Matrix M2)
{
    if (M1.m_rows != M2.m_rows)
        throw "Matrix size's are mismatched";

    Matrix res(M1.m_rows, M1.n_cols + M2.n_cols);

    for (int i = 0; i < res.m_rows; ++i)
    {
        int j = 0;
        for (; j < M1.n_cols; ++j)
            res.values[i*res.n_cols + j] = M1.values[i*M1.n_cols + j];

        for (; j < M1.n_cols + M2.n_cols; ++j)
            res.values[i*res.n_cols + j] = M2.values[i*M2.n_cols + j - M1.n_cols];
    }
    
    return res;
}

Matrix operator / (const Matrix M1, const Matrix M2)
{
    if (M1.n_cols != M2.n_cols)
        throw "Matrix size's are mismatched";

    Matrix res(M1.m_rows + M2.m_rows, M1.n_cols);

    int i = 0;
    for (; i < M1.m_rows; ++i)
    {
        for (int j = 0; j < res.n_cols; ++j)
            res.values[i*res.n_cols + j] = M1.values[i*M1.n_cols + j];
    }
    for (; i < M1.m_rows + M2.m_rows; ++i)
    {
        for (int j = 0; j < res.n_cols; ++j)
            res.values[i*res.n_cols + j] = M2.values[(i - M1.m_rows)*M1.n_cols + j];
    }
    
    return res;
}

Matrix & Matrix::gauss()
{
    int i = 0;
    double del;
    for (int j = 0; j < n_cols; j++)
    {
        swap_max(j, i, del);
        subtract(j, i);
        ++i;
        
    }

    return *this;
}
    
Matrix & Matrix::subtract(const int col, const int line)
{
    long double del;
    for (int i = line + 1; i < m_rows; i++)
    {
        del = (*(values + n_cols*i + col))/(*(values + line*n_cols + col));
        for (int j = col; j < n_cols; j++)
        {
            *(values + n_cols*i + j) = *(values + n_cols*i + j) - (*(values + line*n_cols + j))*del;
        }
    }
    return *this;
}

Matrix & Matrix::swap_max(const int col, const int line, double & del)
{
    long double swap;

    int i_swap1 = line, i_swap2 = line;
    long double max = *(values + line*n_cols + col);
    long double max_sgn = max;

    for (int i = line; i < m_rows; ++i)
    {
        if (fabs(*(values + n_cols*i + col)) > max)
        {
            i_swap2 = i;
            max_sgn = *(values + n_cols*i + col);
            max = fabs(max_sgn);
        }
    }
    
    // std::cout << "max_sng: " << max_sgn << std::endl;
    // std::cout << "max: " << max << std::endl;

    if (max == 0)
    {
        del = 0;
        return *this;
    }

    del *= max_sgn;

    if (i_swap1 != i_swap2)
    {
        for (int i = col; i < n_cols; i++)
        {
            swap = *(values + i_swap1*n_cols + i);
            *(values + i_swap1*n_cols + i) = *(values + i_swap2*n_cols + i);
            *(values + i_swap2*n_cols + i) = swap;
        }
    }

    for (int i = col; i < n_cols; i++)
    {
        *(values + i_swap1*n_cols + i) = *(values + i_swap1*n_cols + i)/max;
    }   
    
    return *this;
}

double Matrix::deteminant()
{
    Matrix tmp(*this);

    if(m_rows != n_cols)
        throw "Can't use this operation: matrix isn't square";

    int i = 0;
    double del = 1;

    for (int j = 0; j < n_cols; j++)
    {
        swap_max(j, i, del);
        if (del == 0)
        {
            break;
        }
        subtract(j, i);
        ++i;   
    }

    *this = tmp;
    // std::cout << "del: " << del << std::endl;
    return del;
}

Matrix Matrix::solve()
{
    Matrix A(m_rows, n_cols - 1);
    Matrix b(m_rows, 1);
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < n_cols - 1; ++j)
        {
            A.values[i*(n_cols-1) + j] = values[i*n_cols + j];
        } 
    }

    for (int i = 0; i < m_rows; ++i)
    {
        b.values[i] = values[i*n_cols + n_cols - 1];
    }
    
    if (A.deteminant() == 0)
        throw "Matrix is degenerate";
    
    gauss();

    Matrix sol(m_rows, 1);
    long double tmp = 0;

    for (int i = m_rows - 1; i >= 0; --i)
    {
        for (int j = i + 1; j <= m_rows; ++j)
        {
            tmp += (*(values + n_cols*i + j))*(*(sol.values + j));
        }

        *(sol.values + i) = (*(values + n_cols*i + m_rows) - tmp)/(*(values + n_cols*i + i));
        tmp = 0;
        
    }

    if(A*sol != b)
        throw "Couldn't find solution";

    return sol;

}

Matrix Matrix::transposition()
{
    if(m_rows != n_cols)
        throw "Can't use this operation: matrix isn't square";
        
    Matrix m_tmp = *this;
    double tmp;
    int j;
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = i; j < n_cols; ++j)
        {
            if (i!=j)
            {
                tmp = m_tmp.values[i*n_cols + j];
                // std::cout << "tmp: " << tmp << std::endl;
                m_tmp.values[i*n_cols + j] = m_tmp.values[j*n_cols + i];
                m_tmp.values[j*n_cols + i] = tmp;
            }
        }
    }

    return m_tmp;
}

Matrix operator ~ (Matrix M)
{
    double d = M.deteminant();
    if (d == 0)
        throw "Matrix is degenerate";

    Matrix M_T(M.m_rows, M.n_cols);

    for (int i = 0; i < M.m_rows; i++)
    {
        for (int j = 0; j < M.n_cols; j++)
        {
            /* code */
        }
        
    }
    

    for (int i = 0; i < M.m_rows*M.n_cols; i++)
    {
        M_T.values[i] /= d;
    }
    
    return M_T;
}