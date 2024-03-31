#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdlib.h>

namespace gameTheoryAndOperationsResearch {
    class gameTheoryAndOperationsResearch_vector
    {
    public:
        void composition_vector_matrix(double *, double **, double*, int, int);
        void composition_matrix_vector(double **, double *,  double*, int, int);
        double composition_vector_vector(double *, double *, int);
        void print_vector(std::ostream& , char *, double *, int );
    };
}

#endif // VECTOR_H
