#include "matrix.h"

namespace gameTheoryAndOperationsResearch {


    // Далее функции для аналитического метода обратной матрицы

    double gameTheoryAndOperationsResearch_matrix::get_determinant_matrix(double **p, int n) // Вычисление определителя матрицы
    {
        if (n == 1) {
            return p[0][0];
        }
        if (n == 2) {
            return p[0][0] * p[1][1] - p[0][1] * p[1][0];
        }
        else
        {
            double **p2 = new double *[n - 1];
            for (int i = 0; i < n - 1; i++)
                p2[i] = new double[n - 1];

            int zn = 1;
            double Det = 0;

            for (int k = 0; k < n; k++, zn *= -1)
            {
                if (p[0][k] == 0)
                    continue;
                for (int i = 1; i < n; i++) {
                    for (int j = 0; j < n; j++)
                    {
                        if (j < k) p2[i - 1][j] = p[i][j];
                        if (j > k) p2[i - 1][j - 1] = p[i][j];
                    }
                }

                Det += zn * p[0][k] * get_determinant_matrix(p2, n - 1);
            }

            for (int i = 0; i < n - 1; i++)
                delete[] p2[i];
            delete[] p2;

            return Det;
        }
    }

    void gameTheoryAndOperationsResearch_matrix::get_inverse_matrix(double p[DEFINE_N1][DEFINE_N1], double **pObr, int n) // Вычисление обратной матрицы для матрицы
    {
        double Det = 0;

        if (n == 2)
        {
            Det = p[0][0] * p[1][1] - p[0][1] * p[1][0];
            pObr[0][0] = p[1][1];
            pObr[0][1] = p[1][0] * -1;
            pObr[1][0] = p[0][1] * -1;
            pObr[1][1] = p[0][0];
        }
        else
        {
            double **p2 = new double *[n - 1];

            for (int i = 0; i < n - 1; i++)
                p2[i] = new double[n - 1];

            int zn = 1;
            Det = 0;

            for (int k0 = 0; k0 < n; k0++)
            {
                for (int k = 0; k < n; k++)
                {
                    if ((k + k0) % 2)
                        zn = -1;
                    else
                        zn = 1;

                    //  if (p[0][k] == 0) continue;
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++)
                        {
                            if (i > k0)
                            {
                                if (j < k) p2[i - 1][j] = p[i][j];
                                if (j > k) p2[i - 1][j - 1] = p[i][j];
                            }
                            if (i < k0)
                            {
                                if (j < k) p2[i][j] = p[i][j];
                                if (j > k) p2[i][j - 1] = p[i][j];
                            }
                        }
                    }

                    double opr = get_determinant_matrix(p2, n - 1);
                    pObr[k0][k] = zn * opr;

                    if (k0 == 0)
                        Det += p[k0][k] * pObr[k0][k];

                }
            }

            for (int i = 0; i < n - 1; i++)
                delete[] p2[i];
            delete[] p2;

        }
        // Транспонируем матрицу
        for (int i = 0; i < n - 1; i++) for (int j = i + 1; j < n; j++)
        {
            double buf = pObr[i][j]; pObr[i][j] = pObr[j][i];
            pObr[j][i] = buf;
        }
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            pObr[i][j] /= Det;
            if (fabs(pObr[i][j]) < 1e-9) pObr[i][j] = 0;
        }
    }
}
