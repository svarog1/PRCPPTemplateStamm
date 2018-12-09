/** PRCPPTemplatesStamm.cpp : This file contains the 'main' function. Program execution begins and ends there. */
/**  */

#include "pch.h"
#include <iostream>
#include "C:\Users\santi\source\repos\PRCPPTemplatesStamm\Vector.cpp"


int main()
{
	Vector<double, 5> A({ 1, 2, 3, 4, 5 });
	Vector<double, 5> B({ 0.5, 1.0, 1.5, 2.0, 2.5 });
	Vector<double, 5> C({ 2, 3, 4, 5, 6 });
	Vector<double, 5> D({ 3, 3, 3, 3, 3 });


	auto e = (A + C + Vector<double, 5>({ 3, 1, -1, -3, -5 })) / 3.0;
	e.print();
	
	auto f = A + D;
	f.print();
	A = f;
	e.print();
	D.print();
	

}
