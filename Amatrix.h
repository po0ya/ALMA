/*
 * Amatrix.h
 *
 *  Created on: Oct 16, 2012
 *      Author: Seyed Abbas Hosseini
 */

#ifndef Amatrix_H_
#define Amatrix_H_

#include<stdlib.h>
#include<cblas.h>
class Avector;
class dummyA;
class Amatrix {
protected:
	double* A;
	size_t rows, columns, step;
	bool isTransposed;
	int shared;
	size_t column_index;
	void init(size_t, size_t,bool); //initializes
public:
	Amatrix(double*, size_t, size_t, size_t, bool); //this constructor is used for getting arrays and rows of the matrix
	//Amatrix(); not useful
	Amatrix(size_t, size_t); // get an empty matrix of size m-by-n which equlas zero
	Amatrix(size_t, size_t, double*, bool);
	Amatrix(Amatrix& B); // Make a copy of B

	virtual ~Amatrix();

	double* asVector(); // getter of the double*
	bool isTrans(); // return whether it's transposed or not
	double getConstant();
	int isShared(); // shows whether the vector is shared between two objects
	size_t getStep();

	Amatrix& operator=(Amatrix& B); // make a copy
	Amatrix& operator=(double val); // assign val to one element
	Amatrix& operator+(double val); // add val to every element
	Amatrix& operator+(Amatrix& B); //
	Amatrix& operator+=(double val); //
	Amatrix& operator+=(Amatrix& B); //
	Amatrix& operator-(double val); // subtracts val from every element
	Amatrix& operator-(Amatrix& B); //
	Amatrix& operator-=(double val); //
	Amatrix& operator-=(Amatrix& B); //
	Amatrix& operator*(double val); // multiplies each element to val
	Amatrix& operator*(Amatrix& B); //
	Amatrix& operator/(double val); // devides each element to val
	double operator!(); // returns what's inside a 1*1 cell
	Amatrix& operator~(); // Transpose operator i.e., ~A=AT
	Amatrix& operator[](size_t); // for two dimensional subscripting - first dimension
	Amatrix& row(size_t);
	Amatrix& column(size_t);
	Amatrix& cloneRow(size_t);
	Amatrix& cloneColumn(size_t);
	size_t row_size();
	size_t column_size();
};

#endif /* Amatrix_H_ */
