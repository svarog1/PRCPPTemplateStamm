#pragma once
#include "pch.h"
#include <cstring>
#include <memory>
#include <iostream>

using namespace std;

//Forward declaration (resolves circular dependencies)
template<typename T, const int n>
struct Array;
template<typename Left, typename Op, typename Right, typename T, const int n>
struct Expr;
template<typename T>
struct Box;

template<typename Left, typename Op, typename Right, typename T, const int n>
struct Expr
{
private:
	Left left;
	Right right;
public:
	Expr(Left l, Right r) : left(l), right(r) { }
	shared_ptr<Array<T, n>> eval() {
		return Op::apply(*left.eval(), *right.eval());
	}
	//Used for **
	Box<Expr<Left, Op, Right, T, n>> operator* () {
		return Box<Expr<Left, Op, Right, T, n>>(*this);
	}
};

template<typename T, const int n>
struct Array
{
private:
	T * data;
public:
	Array(const Array<T, n> & that) {
		this->data = new T[n];
		memcpy(this->data, that.data, n * sizeof(double));
	}
	Array(T * data) : data(data) { }
	~Array() { delete[] data; }

	//Copy Assignement
	void operator=(const Array<T, n> & that) {
		memcpy(this->data, that.data, n * sizeof(double));
	}

	//Assignement over expression
	template<typename Left, typename Op, typename Right>
	void operator=(Expr<Left, Op, Right, T, n> & expr) {
		this->operator=(*expr.eval());
	}

	//[] operator for variables
	T & operator[](int i) {
		return data[i];
	}

	//Additional [] operator for constants
	const T & operator[](int i) const {
		return data[i];
	}

	//Used for **
	Box<Array<T, n>> operator* () {
		return Box<Array<T, n>>(*this);
	}

	shared_ptr<Array<T, n>> eval() {
		return shared_ptr<Array<T, n>>(new Array<T, n>(*this));
	}

	//Print the array to given ostream
	void print(ostream & out) const {
		out << '[';
		if (n > 0) { cout << data[0]; }
		for (int i = 1; i < n; ++i) { cout << ", " << data[i]; }
		cout << ']';
	}
};

//Array print over << operator
template<typename T, const int n>
ostream& operator<<(ostream & os, const Array<T, n> & a) {
	a.print(os);
	return os;
}

//** Operators **//

//Plus operator
template<typename T, const int n>
struct Plus
{
	static shared_ptr<Array<T, n>> apply(const Array<T, n> & left, const Array<T, n> & right) {
		shared_ptr<Array<T, n>> result(new Array<T, n>(new T[n]));
		for (int i = 0; i < n; ++i) {
			(*result)[i] = left[i] + right[i];
		}
		return result;
	}
};

template<typename Left, typename T, const int n>
Expr<Left, Plus<T, n>, Array<T, n>, T, n> operator+(Left left, Array<T, n> right) {
	return Expr<Left, Plus<T, n>, Array<T, n>, T, n>(left, right);
}
template<typename Left, typename subLeft, typename subRight, typename subOp, typename T, const int n>
Expr<Left, Plus<T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n> operator+(Left left, Expr<subLeft, subOp, subRight, T, n> right) {
	return Expr<Left, Plus<T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n>(left, right);
}

//Minus operator
template<typename T, const int n>
struct Minus
{
	static shared_ptr<Array<T, n>> apply(const Array<T, n> & left, const Array<T, n> & right) {
		shared_ptr<Array<T, n>> result(new Array<T, n>(new T[n]));
		for (int i = 0; i < n; ++i) {
			(*result)[i] = left[i] - right[i];
		}
		return result;
	}
};

template<typename Left, typename T, const int n>
Expr<Left, Minus<T, n>, Array<T, n>, T, n> operator-(Left left, Array<T, n> right) {
	return Expr<Left, Minus<T, n>, Array<T, n>, T, n>(left, right);
}
template<typename Left, typename subLeft, typename subRight, typename subOp, typename T, const int n>
Expr<Left, Minus<T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n> operator-(Left left, Expr<subLeft, subOp, subRight, T, n> right) {
	return Expr<Left, Minus<T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n>(left, right);
}

//* operator (Scalar)
template<typename S, typename T, const int n>
struct Scalar
{
	static shared_ptr<Array<T, n>> apply(const Array<S, n> & left, const Array<T, n> & right) {
		shared_ptr<Array<T, n>> result(new Array<T, n>(new T[n]));
		for (int i = 0; i < n; ++i) {
			(*result)[i] = left[i] * right[i];
		}
		return result;
	}
};

template<typename T, const int n>
Array<T, n> createScalar(T & value) {
	T * tmpArray = new T[n];
	fill(tmpArray, tmpArray + n, value);
	Array<T, n> tmp(tmpArray);
	return tmp;
}

template<typename S, typename T, const int n>
Expr<Array<S, n>, Scalar<S, T, n>, Array<T, n>, T, n> operator*(S left, Array<T, n> right) {
	return Expr<Array<S, n>, Scalar<S, T, n>, Array<T, n>, T, n>(createScalar<S, n>(left), right);
}
template<typename subLeft, typename subRight, typename subOp, typename S, typename T, const int n>
Expr<Array<T, n>, Scalar<S, T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n> operator*(S left, Expr<subLeft, subOp, subRight, T, n> right) {
	return Expr<Array<S, n>, Scalar<S, T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n>(createScalar<S, T, n>(left), right);
}
template<typename S, typename T, const int n>
Expr<Array<S, n>, Scalar<S, T, n>, Array<T, n>, T, n> operator*(Array<T, n> left, S right) {
	return right * left;
}
template<typename subLeft, typename subRight, typename subOp, typename S, typename T, const int n>
Expr<Array<T, n>, Scalar<S, T, n>, Expr<subLeft, subOp, subRight, T, n>, T, n> operator*(Expr<subLeft, subOp, subRight, T, n> left, S right) {
	return right * left;
}

//** operator (Scalar Product)
template<typename T, const int n>
struct ScalarProduct
{
	static shared_ptr<Array<T, n>> apply(const Array<T, n> & left, const Array<T, n> & right) {
		shared_ptr<Array<T, n>> result(new Array<T, n>(new T[n]));
		for (int i = 0; i < n; ++i) {
			(*result)[i] = left[i] * right[i];
		}
		return result;
	}
};

template<typename T>
struct Box
{
	T & content;
	Box(T & c) : content(c) { }
};

//** Solution A: With vector as result (not mathematically correct)
/*
template<typename B, typename T, const int n>
Expr<Array<T, n>, ScalarProduct<T, n>, B, T, n> operator*(Array<T, n> left, Box<B> right){
	return Expr<Array<T, n>, ScalarProduct<T, n>, B, T, n>(left, right.content);
}
template<typename B, typename subLeft, typename subRight, typename subOp, typename T, const int n>
Expr<Expr<subLeft, subOp, subRight, T, n>, ScalarProduct<T, n>, B, T, n> operator*(Expr<subLeft, subOp, subRight, T, n> left, Box<B> right){
	return Expr<Expr<subLeft, subOp, subRight, T, n>, ScalarProduct<T, n>, B, T, n>(left, right.content);
}
*/

//**Solution B: With scalar as result (mathematically correct)
template<typename B, typename T, const int n>
T operator*(Array<T, n> left, Box<B> right) {
	Array<T, n> result = *ScalarProduct<T, n>::apply(left, *right.content.eval());
	T total = 0;
	for (int i = 0; i < n; ++i) { total += result[i]; }
	return total;
}
template<typename B, typename subLeft, typename subRight, typename subOp, typename T, const int n>
T operator*(Expr<subLeft, subOp, subRight, T, n> left, Box<B> right) {
	return *left.eval() * right;
}
