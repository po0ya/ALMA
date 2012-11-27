/*
 * Amatrix.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: Pouya Samangouei
 */

#include "Amatrix.h"
#include <cstring>
#include<iostream>
#include<cblas.h>
#include<clapack.h>
using namespace std;

Amatrix::Amatrix(size_t rows, size_t columns) // get an empty matrix of size m-by-n which equlas zero
{
	A = new double[rows * columns];
	memset(A, 0, rows * columns);
	init(rows, columns, false);
	this->shared = 0;
}

Amatrix::Amatrix(size_t rows, size_t columns, double* that, bool isTransposed) {
	A = new double[rows * columns];
	memcpy(A, that, rows * columns * sizeof(double));
	init(rows, columns, isTransposed);
	this->shared = 0;
}

Amatrix::Amatrix(double* that, size_t rows, size_t columns, size_t step,
		bool isTrans) {
	A = that;
	init(rows, columns, isTrans);
	this->shared++;
	this->step = step;
}

Amatrix::Amatrix(Amatrix& B) // Make a copy of B
{
	A = new double[B.row_size() * B.column_size()];
	memcpy(A, B.asVector(), B.row_size() * B.column_size() * sizeof(double));
	init(B.row_size(), B.column_size(), B.isTrans());
	this->shared = 0;

	this->step = B.getStep();
}

Amatrix& Amatrix::operator=(Amatrix& B) {
	/*if (B.column_size() == columns && B.row_size()) {
	 if (B.isShared())
	 cout << "warning: right hand's matrix is shared" << endl;
	 init(B.row_size(),B.column_size(),B.isTrans());
	 cblas_dcopy(rows * columns, B.asVector(),
	 (B.row_size() == 1) ? B.getStep() : 1, A,
	 (row_size() == 1) ? step : 1);
	 }*/
	delete A;
	A = new double[B.row_size() * B.column_size()];
	memcpy(A, B.asVector(), B.row_size() * B.column_size() * sizeof(double));
	init(B.row_size(), B.column_size(), B.isTrans());
	this->shared = 0;
	this->step = B.getStep();
	//else exception
}

void Amatrix::init(size_t rows, size_t columns, bool isTransposed) {
	this->rows = rows;
	this->columns = columns;
	this->step = rows;
	this->isTransposed = isTransposed;

}

Amatrix& Amatrix::operator[](size_t i) {
	Amatrix* dum;
	if (isTransposed) {
		if (rows == 1 && i < columns)
			dum = new Amatrix(A + i, 1, 1, step, isTransposed);
		else if (i < rows)
			dum = new Amatrix(A + i * step, 1, columns, step, isTransposed);
	} else {
		if (rows == 1 && i < columns)
			dum = new Amatrix(A + i * step, 1, 1, step, isTransposed);
		else if (i < rows)
			dum = new Amatrix(A + i, 1, columns, step, isTransposed);
	}

	return *dum;
}

double Amatrix::operator!() {
	if (columns == 1 and rows == 1)
		return (*A);
	//else exception
}

Amatrix& Amatrix::row(size_t i) {
	if (i >= rows) {
		//exception
	} else {
		Amatrix* temp = new Amatrix(A + i, 1, columns, step, isTransposed);
		return *temp;
	}
}

Amatrix& Amatrix::column(size_t i) {
	if (i >= columns) {
		//exception
	} else {
		Amatrix* temp = new Amatrix(A + i * step, rows, 1, step, isTransposed);
		return *temp;
	}
}

Amatrix& Amatrix::cloneRow(size_t i) {
	if (isTransposed) {
		if (i >= columns) {
			//exception
		} else {
			Amatrix* temp = new Amatrix(A + i * step, rows, 1, step,
					isTransposed);
			return *temp;
		}
	}
	if (i >= rows) {
		//exception
	} else {
		Amatrix * ret = new Amatrix(rows, 1);
		cblas_daxpy(rows, 1, A + i, rows, ret->asVector(), 1);
		return *ret;
	}
}

int Amatrix::isShared() {
	return shared;
}

Amatrix& Amatrix::cloneColumn(size_t i) {
	if (isTransposed) {
		if (i >= rows) {
			//exception
		} else {
			Amatrix * ret = new Amatrix(rows, 1);
			cblas_daxpy(rows, 1, A + i, rows, ret->asVector(), 1);
			return *ret;
		}
	}
	if (i >= columns) {
		//exception
	} else {
		Amatrix* temp = new Amatrix(A + i * step, rows, 1, step, isTransposed);
		return *temp;
	}
}

double* Amatrix::asVector() {
	return A;
}

bool Amatrix::isTrans() {
	return isTransposed;
}

size_t Amatrix::row_size() {
	return rows;
}

size_t Amatrix::column_size() {
	return columns;
}

Amatrix::~Amatrix() {
	if (shared == 0)
		delete A;
	else
		shared--;
}

Amatrix& Amatrix::operator *(const double val) {
	Amatrix * temp = new Amatrix(rows, columns);
	cblas_daxpy(rows * columns, val, A, 1, temp->asVector(), 1);
	return *temp;
}

Amatrix& Amatrix::operator /(const double val) {
	Amatrix * temp = new Amatrix(rows, columns);
	cblas_daxpy(rows * columns, 1 / val, A, 1, temp->asVector(), 1);
	return *temp;
}

Amatrix& Amatrix::operator *(Amatrix& B) {
	Amatrix * temp = new Amatrix(rows, B.column_size());
	cblas_dgemm(CblasColMajor, this->isTrans() ? CblasTrans : CblasNoTrans,
			((Amatrix&) B).isTrans() ? CblasTrans : CblasNoTrans, rows,
			B.column_size(), columns, 1.0, A,isTransposed? columns: rows, ((Amatrix&) B).asVector(),
			B.isTrans()? B.column_size():B.row_size(), 0.0, temp->asVector(), rows);
	return *temp;
}

size_t Amatrix::getStep() {
	return step;
}

Amatrix& Amatrix::operator+(double val) {
	Amatrix*temp = new Amatrix(*this);
	(*temp) += val;
	return *temp;
}

Amatrix& Amatrix::operator-(double val) {
	Amatrix*temp = new Amatrix(*this);
	(*temp) -= val;
	return *temp;
}

Amatrix& Amatrix::operator+=(double val) {
	double * temp = new double[rows * columns];
	fill_n(temp, rows * columns, 1);
	cblas_daxpy(rows * columns, val, temp, 1, A, rows == 1 ? step : 1);
	//	delete temp;
}

Amatrix& Amatrix::operator+(Amatrix& B) {
	if (B.row_size() == rows && B.column_size() == columns) {
		Amatrix*temp = new Amatrix(*this);
		(*temp) += B;
		return *temp;
	} else
		cout << " SUM ERR: dimmensions don't match" << endl;
}

Amatrix& Amatrix::operator-(Amatrix& B) {
	if (B.row_size() == rows && B.column_size() == columns) {
		Amatrix*temp = new Amatrix(*this);
		(*temp) -= B;
		return *temp;
	}
	//else exception
}

Amatrix& Amatrix::operator+=(Amatrix& B) {
	if (B.isTrans()) {
		Amatrix*temp = new Amatrix(B);
		*(this) += *temp;
	} else if (B.row_size() == rows && B.column_size() == columns)
		cblas_daxpy(rows * columns, 1, B.asVector(), 1, A, rows == 1 ? step : 1);
	else
		cout << " SUM = ERR: dimmensions don't match" << endl;
}

Amatrix& Amatrix::operator-=(Amatrix& B) {
	if (B.isTrans()) {
		Amatrix*temp = new Amatrix(B);
		*(this) -= *temp;
	} else if (B.row_size() == rows && B.column_size() == columns)
		cblas_daxpy(rows * columns, -1, B.asVector(), 1, A, rows == 1 ? step
				: 1);
	//else exception
}

Amatrix& Amatrix::operator-=(double val) {

	double * temp = new double[rows * columns];
	fill_n(temp, rows * columns, -1);
	cblas_daxpy(rows * columns, val, temp, 1, A, 1);
}

Amatrix& Amatrix::operator =(const double val) {
	if (columns == 1 && rows == 1)
		*A = val;
	return *this;
	//else exception
}

Amatrix& Amatrix::gsle(Amatrix&B) {
	//if(rows!=columns && rows != B.row_size())
	//exception
	Amatrix* tempA = new Amatrix(*this);
	Amatrix* tempB = new Amatrix(B);
	int* tempIPIV = new int[rows];
	int result;
	result = clapack_dgesv(CblasColMajor, rows, B.column_size(),
			tempA->asVector(), rows, tempIPIV, tempB->asVector(), B.row_size());
	return *tempB;
	//if(result!=0)
	//exception
}

Amatrix& Amatrix::operator~() {
	Amatrix* temp = new Amatrix(A, columns, rows, step, !isTransposed);
	return *temp;
	//else exception
}
