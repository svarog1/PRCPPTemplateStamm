/** PRCPPTemplatesStamm.cpp : This file contains the 'main' function. Program execution begins and ends there. */
/**  */

#include "pch.h"
#include <iostream>
#include "Vector.cpp"


int main()
{
	{
	Vector<double, 4> A({ 1, 2, 3, 4 });
	Vector<double, 4> B({ 2, 1, 0, 1 });
	Vector<double, 4> D = A + B;
	auto e = (A - B) * (A + B);
	D = e;
	cout << "e" << e << endl;
	cout << "D" << D << endl;
	cout << D << endl; // [-3,3,9,15]
	B = { 3, 0, 2, 5 };
	cout << e << endl; // [-8,4,5,-9]
	B = { 4, 3, 3, -2 };
	cout << e[1] << endl; // -5

	auto exp1 = A + B;
	auto exp2 = B + A;
	cout << exp1 << exp2 << endl;

	
	
	cout << A << B << D << endl;
	}


	Vector<double, 5> A({ 1, 2, 3, 4, 5 });
	Vector<double, 5> B({ 0.5, 1.0, 1.5, 2.0, 2.5 });
	Vector<double, 5> C({ 2, 3, 4, 5, 6 });
	Vector<double, 5> D({ 3, 3, 3, 3, 3 });
	auto e = (A + C + Vector<double, 5>({ 3, 1, -1, -3, -5 })) / 3.0;
	Vector<double, 5> G();
	Vector<double, 5> E = e;
	auto f = A + D;
	A = f;
	E = e;

	bool alskdfj = (E == D);
	bool asdf = (e == D);

}
