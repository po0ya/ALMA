This library efficiently eases matrix manuplation in C++. It's indeed a wrapper for ATLAS(Automatically Tuned Linear Algebra Software. 
Then it's required to build and install ATLAS from Automatically Tuned Linear Algebra Software.
It can be found in: http://math-atlas.sourceforge.net/
It's needed to compile ATLAS with LAPACK from http://www.netlib.org/lapack/

Look at example.cpp to see how to use ALMA.
In short, Amatrix class has a column major array and stores number of rows and columns etc.

The following operators are implemented:

Amatrix +*-/ double = Amatrix

Amatrix +*-/ Amatrix = Amatrix

X= A.inv(B) -> solves A * X = B which is a general system of linear equations.
