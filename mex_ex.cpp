#include "mex.h"
#include "Amatrix.h"

void mexFunction(int nlhs,mxArray* plhs[],int rhs,const mxArray* prhs[]){
    	double A[] = {1,2,3,3,5,6,9,8,9};
        Amatrix tempA(3, 3, A, false);
}