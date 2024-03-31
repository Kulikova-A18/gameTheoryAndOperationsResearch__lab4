#include "vector.h"

namespace gameTheoryAndOperationsResearch {
    // Произведение вектора на матрицу
    void gameTheoryAndOperationsResearch_vector::composition_vector_matrix(double *v, double **matr, double* v_out, int n, int m)
    {
        for (int i = 0; i < m; i++)
        {
            v_out[i] = 0;

            for (int j = 0; j < n; j++)
                v_out[i] += v[j] * matr[j][i];

        }
    }

    // Произведение матрицы на вектор
    void gameTheoryAndOperationsResearch_vector::composition_matrix_vector(double **matr, double *v,  double* v_out, int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            v_out[i] = 0;

            for (int j = 0; j < m; j++)
                v_out[i] += v[j] * matr[i][j];

        }
    }

    // Произведение вектор на вектор - на выходе число (скалярное произведение)
    double gameTheoryAndOperationsResearch_vector::composition_vector_vector(double *v1, double *v2, int n)
    {
        double rez = 0;

        for (int i = 0; i < n; i++)
            rez += v1[i] * v2[i];

        return rez;
    }

    void gameTheoryAndOperationsResearch_vector::print_vector(std::ostream& out, char * str, double *p, int n)
    {
        out.precision(3);
        out << str << ": ";

        for (int i = 0; i < n; i++)
            out << p[i] << " ";

        out << std::endl;
    }
}
