// PRCPPTemplatesStamm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "C:\Users\santi\source\repos\PRCPPTemplatesStamm\Vector.cpp"


int main()
{
	Vector<double, 5> A({ 1, 2, 3, 4, 5 });
	Vector<double, 5> B({ 1, 4, 9, 16, 25 });
	Vector<double, 5> C({ 2, 6, 12, 20, 30 });
	Vector<double, 5> Q = (A**B)*(A + B) / (B**A);
	Vector<double, 5> a = (C - B);
	
	Vector<double, 5> b = (A**B)*(A + B);
	double c = (B**A);
	Vector<double, 5> d = b / c;
	

	a.print();
	b.print();
	//c.print();
	d.print();
	std::cout << "Hello World!\n";

}
