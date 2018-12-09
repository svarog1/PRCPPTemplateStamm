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

	Vector<double, 5> D = A + B;
	A.print();
	B.print();
	D.print();

	D = 5+D;
	D.print();

    bool r1= (A*A == B);

	/*	Assert::IsTrue(B[4] == (A*A)[4]);
	Assert::IsTrue(B/A == A);
	Assert::IsTrue(A[3] == (B/A)[3]);

	Assert::IsTrue(C == A + B);
	Assert::IsTrue(C[2] == (B + A)[2]);

	Assert::IsTrue(C - A == B);
	Assert::IsTrue(A[1] == (C - B)[1]);*/

	std::cout << "Hello World!\n";
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
