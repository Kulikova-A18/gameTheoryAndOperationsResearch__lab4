#ifndef MATRIX_H
#define MATRIX_H

#include "main.define.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdlib.h>

namespace gameTheoryAndOperationsResearch {
    class gameTheoryAndOperationsResearch_matrix
    {
        public:

            double get_determinant_matrix(double**, int);
            void get_inverse_matrix(double p[DEFINE_N1][DEFINE_N1], double**, int);
        };
}

#endif // MATRIX_H
