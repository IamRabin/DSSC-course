/*
## Matrix transpose

- Write a function that computes the transpose of a mymatrixrix.
The mymatrixrix is represented by a simple `std::array<double,N>` where N is
the total size of the mymatrixrix (i.e., number of rows times number of columns). 
The original array must be modified inside the  function `transpose`.

*Hints*:

- In C/C++, the mymatrixrices are accessed row-wise
- Don't try to use that for very big mymatrixrices, otherwise you go in stack
  overflow.
- You are not required to do the transpose *in place*.
- Test with both square and rectangular mymatrixrices.
*/

#include<iostream>
#include <array>


template<int size>
class Matrix
{

    private:
        std::array<double, size> Mx;
        int m_rows,m_columns;


    public:
        Matrix(const int rows, const int columns)
        {
            m_rows = rows;
            m_columns = columns;

            double incre = 0.0;

            for(int i = 0; i < m_rows; i++)
            {
                for(int j = 0; j < m_columns; j++)
                {
                    int pos = j + i * m_columns;
                    Mx[pos] = incre++;
                }

            }
        }

        const int rows() const
            {
                return m_rows;
             }

        const int columns() const
         {
             return m_columns;
          }

        /**
        Transposing the matrix within.
        */

        void transpose()
        {
            std::array<double, size> transpose;

            for(int j = 0; j < m_rows; j++)
            {
                for(int i = 0; i < m_columns; i++)
                {
                    transpose[j * m_columns + i] = Mx[i * m_rows + j];
                }
            }

            Mx = transpose;

            int tmp = m_rows;
            m_rows = m_columns;
            m_columns = tmp;
        }

        const double& operator[](const std::size_t i) const
         {
             return Mx[i];
         }
};


template <int size>
std::ostream& operator<<(std::ostream& os, const Matrix<size>& mat)
{
    for(int i = 0; i < mat.columns(); i++)
    {
        for(int j = 0; j < mat.rows(); j++)
        {
            int pos = j + i * mat.rows();
            os << mat[pos] << " ";
        }

        os << std::endl;
    }
    os << std::endl << std::endl;
    return os;
}



int main()
{
    const int SIZE = 9;

    // Squared Matrix
    Matrix<SIZE> mymatrix = Matrix<SIZE>(3, 3);
    std::cout << mymatrix << std::endl;
    mymatrix.transpose();
    std::cout << "Transpose of the Matrix is..." << mymatrix << std::endl;

    // Rectangular Matrix
    Matrix<SIZE> mymatrix2 = Matrix<SIZE>(3, 2);
    std::cout << mymatrix2 << std::endl;
    mymatrix2.transpose();
    std::cout << "Transpose of the Matrix is...."<< mymatrix2 << std::endl;
    return 0;
}
