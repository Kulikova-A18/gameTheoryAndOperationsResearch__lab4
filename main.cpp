#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "main.define.h"

#include "vector.h"
#include "matrix.h"
//#include "metodsparetonesh.h"

namespace gameTheoryAndOperationsResearch {
    void _gameTheoryAndOperationsResearch_readfile() {
        std::string line;std::ifstream in(gameTheoryAndOperationsResearch_filename);
        while (std::getline(in, line))
            std::cout << line << std::endl;
    }

    void _gameTheoryAndOperationsResearch_deletefile() {
        std::remove(gameTheoryAndOperationsResearch_filename);
    }
    gameTheoryAndOperationsResearch_matrix _gameTheoryAndOperationsResearch_matrix_main;
    gameTheoryAndOperationsResearch_vector _gameTheoryAndOperationsResearch_vector_main;

    double M1[DEFINE_N1][DEFINE_N1] = { { 4, 5 },
                                        { 0, 7 } }; // Матрица для 1-го игрока
    double M2[DEFINE_N1][DEFINE_N1] = { { 7, 2 },
                                        { 2, 3} }; // Матрица для 2-го игрока

    // Проверка принадлежит ли решение с индексами i1 и j1 множеству Парето
    // Исходные матрицы передаются через указатели
    template<typename T>
    bool is_lot_of_Pareto(T *M1, T *M2, int n, int i1, int j1)
    {
        T Val1 = *(M1 + i1 * n + j1);
        T Val2 = *(M2 + i1 * n + j1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!((i == i1) && (j == j1))) // Просматриваем все элементы кроме заданного
                    if ((*(M1 + i * n + j) >= Val1 && *(M2 + i * n + j) > Val2) ||
                        (*(M1 + i * n + j) > Val1 && *(M2 + i * n + j) >= Val2))
                        return false;  // Нашли решение, которое доминирует, решение не принадлежит множеству Парето
        if(Val1 == Val2)
            return false;

        return true; // Не нашли доминирующего решения, значит решение принадлежит множеству Парето
    }

    // Проверка принадлежит ли решение с индексами i1 и j1 множеству Неша
    template<typename T>
    bool is_lot_of_Nesh(T *M1, T *M2, int n, int i1, int j1)
    {
        T Val1 = *(M1 + i1 * n + j1);
        T Val2 = *(M2 + i1 * n + j1);
        // Проверяем может ли первый игрок улучшить свое решение
        for (int i = 0; i < n; i++)
            if (i != i1)
                if (*(M1 + i * n + j1) > Val1)
                    return false; // Первый игрок может улучшить свое решение при заданном решении 2-го игрока, решение не принадлешит Нешу

        // Проверяем может ли второй игрок улучшить свое решение
        for (int j = 0; j < n; j++)
            if (j != j1)
                if (*(M2 + i1 * n + j) > Val2)
                    return false; // Второй игрок может улучшить свое решение при заданном решении 1-го игрока, решение не принадлехит Нешу

        if(Val1 == Val2)
            return false;

        return true; // Решение принадлежит Нешу
    }

    // Печать матрицы c заголовком
    template<typename T>
    void  print_matrix(std::ostream & out, char *text, T *M, int n)
    {
        out << text << ":" << std::endl; // Печать заголовка

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) {
                out.width(5);
                out << *(M + i * n + j);
            }
            out << std::endl;
        }
    }

    int _main(int argc, char* argv[])
    {
        srand(time(0));
        int M22_1[DEFINE_N2][DEFINE_N2], M22_2[DEFINE_N2][DEFINE_N2];   // Матрицы 10 х 10 для заполнения псевдослуч числами

        int N = 15;

        int M1_1[DEFINE_N1][DEFINE_N1] = { { rand() % N, rand() % N },
                                           { rand() % N, rand() % N } }; // The 1st 2x2 matrix for the Prisoner's «Dilemma game»
        int M1_2[DEFINE_N1][DEFINE_N1] = { { rand() % N, rand() % N },
                                           { rand() % N, rand() % N} }; // The 1st 2x2 matrix for the game  «Family Dispute»
        int M1_3[DEFINE_N1][DEFINE_N1] = { { rand() % N, rand() % N },
                                           { rand() % N, rand() % N }}; // The 1st 2x2 matrix for the game "Crossroads"

        int M2_1[DEFINE_N1][DEFINE_N1] = { { rand() % N, rand() % N },
                                           { rand() % N, rand() % N } }; // The 2st 2x2 matrix for the Prisoner's «Dilemma game»
        int M2_2[DEFINE_N1][DEFINE_N1] = { { rand() % N, rand() % N },
                                           { rand() % N, rand() % N } }; // The 2st 2x2 matrix for the game  «Family Dispute»
        int M2_3[DEFINE_N1][DEFINE_N1] = { { rand() % N, rand() % N },
                                           { rand() % N, rand() % N } }; // The 2st 2x2 matrix for the game «Crossroads»

        // Удаляем файл
        _gameTheoryAndOperationsResearch_deletefile();

        std::ofstream fout(gameTheoryAndOperationsResearch_filename);

        fout << "****GENERATION START****" << std::endl;
        fout << "[Dilemma game]" << std::endl;
        print_matrix(fout,  (char *)"M1_1", (int *)M1_1, (int)DEFINE_N1);
        print_matrix(fout,  (char *)"M2_1", (int *)M2_1, (int)DEFINE_N1);
        fout << "[Family Dispute]" << std::endl;
        print_matrix(fout,  (char *)"M1_2", (int *)M1_2, (int)DEFINE_N1);
        print_matrix(fout,  (char *)"M2_2", (int *)M2_2, (int)DEFINE_N1);
        fout << "[Crossroads]" << std::endl;
        print_matrix(fout,  (char *)"M1_3", (int *)M1_3, (int)DEFINE_N1);
        print_matrix(fout,  (char *)"M2_3", (int *)M2_3, (int)DEFINE_N1);
        fout << "****GENERATION END****\n" << std::endl;

        // заполняем матрцы ПСЧ
        for(int i=0; i<DEFINE_N2; i++) {
            for (int j = 0; j < DEFINE_N2; j++)
            {
                M22_1[i][j] = rand() % 20;
                M22_2[i][j] = rand() % 20;
            }
        }

        print_matrix(fout,  (char *)"The 1st matrix is 10x10", (int *)M22_1, (int)DEFINE_N2);
        print_matrix(fout, (char *)"The 2st matrix is 10x10", (int *)M22_2, DEFINE_N2);

        // Поиск множества Парето
        fout << "\n[The Pareto solution]" << std::endl;
        for (int i = 0; i < DEFINE_N2; i++)
            for (int j = 0; j < DEFINE_N2; j++)
                if (is_lot_of_Pareto((int *)M22_1, (int *)M22_2, DEFINE_N2, i, j)) {// Нашли решение из множества Парето
                    fout << "\ti: " << (i + 1) << "\tj: " << (j + 1) << "\tM1: " << M22_1[i][j] << "\tM2: " << M22_2[i][j] << std::endl;
                }

        fout << "\n[The Nash solution]" << std::endl;
        bool flag = false;
        for (int i = 0; i < DEFINE_N2; i++)
            for (int j = 0; j < DEFINE_N2; j++)
                if (is_lot_of_Nesh((int *)M22_1, (int *)M22_2, DEFINE_N2, i, j)) // Нашли решение из множества Неша
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M22_1[i][j]
                         << "\tM2: " << M22_2[i][j]
                         << std::endl;
                    flag = true;
                }
        if (!flag) {
                fout << "[!] There is no Nash solution in pure strategies" << std::endl;
        }

        print_matrix(fout, (char *)"The 1st 2x2 matrix for the Prisoner's «Dilemma game»", (int *)M1_1, DEFINE_N1);
        print_matrix(fout, (char *)"The 2st 2x2 matrix for the Prisoner's «Dilemma game»", (int *)M2_1, DEFINE_N1);

        // Поиск множества Парето
        fout << "\n[The Pareto solution]" << std::endl;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Pareto((int *)M1_1, (int *)M2_1, DEFINE_N1, i, j)) // Нашли решение из множества Парето
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1_1[i][j]
                         << "\tM2: " << M2_1[i][j]
                            << std::endl;
                }

        fout << "\n[The Nash solution]" << std::endl;
        flag = false;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Nesh((int *)M1_1, (int *)M2_1, DEFINE_N1, i, j)) // Нашли решение из множества Неша
                {
                    fout << "\ti: " << (i + 1) << "\tj: " << (j + 1) << "\tM1: " << M1_1[i][j] << "\tM2: " << M2_1[i][j] << std::endl;
                    flag = true;
                }
        if (!flag) {
            fout << "\n[!] There is no Nash solution in pure strategies" << std::endl;
        }

        print_matrix(fout, (char *)"The 1st 2x2 matrix for the game  «Family Dispute»", (int *)M1_2, DEFINE_N1);
        print_matrix(fout, (char *)"The 2st 2x2 matrix for the game  «Family Dispute»", (int *)M2_2, DEFINE_N1);

        // Поиск множества Парето
        fout << "\n[The Pareto solution]" << std::endl;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Pareto((int *)M1_2, (int *)M2_2, DEFINE_N1, i, j)) // Нашли решение из множества Парето
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1_2[i][j]
                         << "\tM2: " << M2_2[i][j]
                         << std::endl;
                }

        fout << "\n[The Nash solution]" << std::endl;
        flag = false;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Nesh((int *)M1_2, (int *)M2_2, DEFINE_N1, i, j)) // Нашли решение из множества Неша
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1_2[i][j]
                         << "\tM2: " << M2_2[i][j]
                         << std::endl;
                    flag = true;
                }
        if (!flag) {
                fout << "\n[!] There is no Nash solution in pure strategies" << std::endl;
        }

        print_matrix(fout, (char *)"The 1st 2x2 matrix for the game «Crossroads»", (int *)M1_3, DEFINE_N1);
        print_matrix(fout, (char *)"The 2st 2x2 matrix for the game «Crossroads»", (int *)M2_3, DEFINE_N1);

        // Поиск множества Парето
        fout << "\n[The Pareto solution]:" << std::endl;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Pareto((int *)M1_3, (int *)M2_3, DEFINE_N1, i, j)) // Нашли решение из множества Парето
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1_3[i][j]
                         << "\tM2: " << M2_3[i][j]
                         << std::endl;
                }

        fout << "\n[The Nash solution]" << std::endl;
        flag = false;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Nesh((int *)M1_3, (int *)M2_3, DEFINE_N1, i, j)) // Нашли решение из множества Неша
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1_3[i][j]
                         << "\tM2: " << M2_3[i][j]
                         << std::endl;
                    flag = true;
                }
        if (!flag) {
                fout << "\n[!] There is no Nash solution in pure strategies" << std::endl;
        }

        print_matrix(fout, (char *)"The 1st 2x2 matrix from the given option", (double *)M1, DEFINE_N1);
        print_matrix(fout, (char *)"The 2st 2x2 matrix from the given option", (double *)M2, DEFINE_N1);

        // Поиск множества Парето
        fout << "\n[The Pareto solution]" << std::endl;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Pareto((double *)M1, (double *)M2, DEFINE_N1, i, j)) // Нашли решение из множества Парето
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1[i][j]
                         << "\tM2: " << M2[i][j]
                         << std::endl;
                }

        fout << "\n[The Nash solution]" << std::endl;
        flag = false;
        int Num=0;
        for (int i = 0; i < DEFINE_N1; i++)
            for (int j = 0; j < DEFINE_N1; j++)
                if (is_lot_of_Nesh((double *)M1, (double *)M2, DEFINE_N1, i, j)) // Нашли решение из множества Неша
                {
                    fout << "\ti: " << (i + 1)
                         << "\tj: " << (j + 1)
                         << "\tM1: " << M1[i][j]
                         << "\tM2: " << M2[i][j]
                         << std::endl;
                    flag = true;
                    Num++;
                }
        if (!flag) {
                fout << "\n[!] There is no Nash solution in pure strategies" << std::endl;
        }

        fout<<"\n[!] The solution is in mixed strategies"<<std::endl;

        if (Num!=1)
        {

            double *p = new double[DEFINE_N1]; double *q = new double[DEFINE_N1];

            double **c = new double *[DEFINE_N1]; // Обратная матрица
            for (int i = 0; i < DEFINE_N1; i++)
                c[i] = new double[DEFINE_N1];
            _gameTheoryAndOperationsResearch_matrix_main.get_inverse_matrix(M2, c, DEFINE_N1); // Получаем обратную матрицу

            double * u = new double[DEFINE_N1]; // Вспомогательный вектор из всех 1
            for (int i = 0; i < DEFINE_N1; i++)
                u[i] = 1;

            double * r1 = new double[DEFINE_N1]; // Вектор для промежуточных вычислений
            _gameTheoryAndOperationsResearch_vector_main.composition_vector_matrix(u, c, r1, DEFINE_N1, DEFINE_N1);
            double v2 = _gameTheoryAndOperationsResearch_vector_main.composition_vector_vector(r1, u, DEFINE_N1);
            _gameTheoryAndOperationsResearch_vector_main.composition_vector_matrix(u, c, p, DEFINE_N1, DEFINE_N1);
            for (int i = 0; i < DEFINE_N1; i++)
                p[i] /= v2;

            _gameTheoryAndOperationsResearch_vector_main.print_vector(fout, (char *)"x", p, DEFINE_N1);

            _gameTheoryAndOperationsResearch_matrix_main.get_inverse_matrix(M1, c, DEFINE_N1); // Получаем обратную матрицу

            _gameTheoryAndOperationsResearch_vector_main.composition_vector_matrix(u, c, r1, DEFINE_N1, DEFINE_N1);
            double v1 = _gameTheoryAndOperationsResearch_vector_main.composition_vector_vector(r1, u, DEFINE_N1);

            _gameTheoryAndOperationsResearch_vector_main.composition_matrix_vector(c, u, q, DEFINE_N1, DEFINE_N1);
            for (int i = 0; i < DEFINE_N1; i++)
                q[i] /= v1;

            _gameTheoryAndOperationsResearch_vector_main.print_vector(fout, (char *)"y", q, DEFINE_N1);

            fout << std::fixed << std::setprecision(3);
            fout << "v1:    " << 1/v1 << std::endl;
            fout << "v2:    " << 1/v2 << std::endl;
        }
        else
        {
            fout<<"\n[!] One player has a strictly dominant strategy, there is only one Nash solution"<<std::endl;
        }

        // Считываем файл
        _gameTheoryAndOperationsResearch_readfile();

        return 1;
        return 0;
    }
}

int main(int argc, char* argv[])
{
    gameTheoryAndOperationsResearch::_main(argc, argv);
    return 0;
}
