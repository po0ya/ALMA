#include <iostream>
#include "Amatrix.h"
using namespace std;
void printMatrix(Amatrix& in);
void printAsvector(Amatrix& in);
int main() {
	double A[] = { 1, 2, 3, 3, 5, 6, 9, 8, 9 };
	double B[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	double C[] = { 1, 1, 1, 0, 0, 0 };
	double F[] = { 1, 0, 1, 0, 1, 0 };
	double D[] = { 1, 2, 3 };
	Amatrix tempA(3, 3, A, false);
	Amatrix tempB(3, 3, B, false);
	Amatrix tempC(3, 2, C, false);
	Amatrix tempF(2, 3, F, false);
	Amatrix tempD(3, 1, D, false);

	printMatrix(tempA);
//	printMatrix(tempA - tempB);
//	printMatrix(tempA + tempB);
//	printMatrix(tempA * tempB);
//	printMatrix(tempB + 2);
//	printMatrix(tempB - 1);
//	printMatrix(tempB * 3);
//	printMatrix(tempB / 2);
	/*printMatrix(~tempC);
	Amatrix tempG(~tempF);
	printMatrix(tempF);
	printMatrix(tempG);
	*/
	tempF[0][1] = 3;
	printMatrix(~tempC);
	printMatrix(~tempF);
	printMatrix( (tempF)*(~tempA));
	tempA = (tempF)*(~tempA)/2;
	printMatrix(tempA);
	cout<<(tempF).row_size()<<"col: "<<(tempF).column_size()<<endl;
	cout<<(~tempC).row_size()<<"col: "<<(~tempC).column_size()<<endl;
//	printMatrix(tempA.gsle(tempD));
//	printMatrix(~tempF);
//	tempA = ((~tempF) * (~tempC));
//	printMatrix(tempA);
	return 0;
}

void printAsvector(Amatrix& in){
	double* t = in.asVector();
	cout<<"{";
	for(unsigned int i=0;i<in.row_size()*in.column_size();i++)
	{
		cout<<t[i]<<",";
	}
	cout<<"}"<<endl;
}

void printMatrix(Amatrix& in) {
	cout << "{" << endl;
		for (unsigned int i = 0; i < in.row_size(); i++) {
			for (unsigned int j = 0; j < in.column_size(); j++)
				cout << !(in[i][j]) << "\t";
			cout << endl;
		}
	cout << "}" << endl;
}
