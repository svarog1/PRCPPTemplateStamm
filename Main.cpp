#pragma once
#include "pch.h"
#include <iostream>
#include "C:\Users\santi\source\repos\PRCPPTemplatesStamm\Source.cpp"

using namespace std;

int main(void) {
	Array<double, 4> A(new double[4]{ 2, 3, 5, 9 });
	Array<double, 4> B(new double[4]{ 1, 0, 0, 1 });
	Array<double, 4> C(new double[4]{ 3, 0, 2, 5 });
	Array<double, 4> D(new double[4]);

	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C: " << C << endl;
	cout << "D: " << "not initialized" << endl << endl;
	/*
	Result:
	A: [2, 3, 5, 9]
	B: [1, 0, 0, 1]
	C: [3, 0, 2, 5]
	D: not initialized
	*/

	//Test addition
	D = A + B + C;
	cout << "A + B + C =\t" << D << endl;
	D = A + (B + C);
	cout << "A + (B + C) =\t" << D << endl;
	D = (A + B) + C;
	cout << "(A + B) + C =\t" << D << endl;
	D = (B + B) + (B + B);
	cout << "(B + B) + (B + B) =\t" << D << endl << endl;
	/*
	Result:
	A + B + C =     [6, 3, 7, 15]
	A + (B + C) =   [6, 3, 7, 15]
	(A + B) + C =   [6, 3, 7, 15]
	(B + B) + (B + B) =     [4, 0, 0, 4]
	*/

	//Test substraction
	D = A - B - C;
	cout << "A - B - C =\t" << D << endl;
	D = A - (B - C);
	cout << "A - (B - C) =\t" << D << endl;
	D = (A - B) - C;
	cout << "(A - B) - C =\t" << D << endl;
	D = (B - B) - (B + B);
	cout << "(B - B) - (B + B) =\t" << D << endl << endl;
	/*
	Result:
	A - B - C =     [-2, 3, 3, 3]
	A - (B - C) =   [4, 3, 7, 13]
	(A - B) - C =   [-2, 3, 3, 3]
	(B - B) - (B + B) =     [-2, 0, 0, -2]
	*/

	int k = 5;
	double l = 3.14;
	D = k * B;
	cout << "k*B =\t" << D << endl;
	D = k * A + B + l * C;
	cout << "k*A + B + l*C =\t" << D << endl;
	D = A * k + B + C * l;
	cout << "A*k + B + C*l =\t" << D << endl << endl;
	/*
	Result:
	k*B =   [5, 0, 0, 5]
	k*A + B + l*C = [20.42, 15, 31.28, 61.7]
	A*k + B + C*l = [20.42, 15, 31.28, 61.7]
	*/

	//Works with Solution A (see source.cpp)
	/*
	D = A**B;
	cout << "A**B =\t" << D << endl;
	D = B**A;
	cout << "B**A =\t" << D << endl;
	D = A**B**C;
	cout << "A**B**C =\t" << D << endl;
	D = (A**B)**(C**B);
	cout << "(A**B)**(C**B) =\t" << D << endl;
	*/
	/*
	Result:
	A**B =  [2, 0, 0, 9]
	B**A =  [2, 0, 0, 9]
	A**B**C =       [6, 0, 0, 45]
	(A**B)**(C**B) =        [6, 0, 0, 45]
	*/

	//Works with Solution B (see source.cpp)
	double result;
	result = A * *B;
	cout << "A**B =\t" << result << endl;
	result = B * *A;
	cout << "B**A =\t" << result << endl;
	result = (A*k + B + C * l) ** B;
	cout << "(A*k + B + C*l) ** B =\t" << result << endl;
	D = A * *B*B; //equal to (A**B)*B = 11*[1,0,0,1]
	cout << "A**B*B =\t" << D << endl;
	result = C * *B;
	cout << "C**B =\t" << result << endl;
	result = A * *B * C**B;
	cout << "A**B * C**B =\t" << result << endl;
	/*
	Result:
	A**B =  11
	B**A =  11
	(A*k + B + C*l) ** B =  82.12
	A**B*B =        [11, 0, 0, 11]
	C**B =  8
	A**B * C**B =   88
	*/

	getchar();
}