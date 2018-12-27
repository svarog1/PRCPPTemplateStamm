#pragma once
#include <memory>
#include "pch.h"
#include <iostream>
#include "Expression.cpp"
#include <cstring>

using namespace std;

template<class T, const int sizeL>
class Vector {
private:
	T * m_data;

	void print(ostream & out) const
	{
		out << "[";
		for (size_t i = 0; i < size(); i++)
		{
			if (i>0)
			{				
				out << ", " ;
			}
			out << m_data[i] << " ";
			

		}
		out << "]";
	}

public:
	/** return array size. */
	int size() const {
		return sizeL;
	}

	Vector(const std::initializer_list<T>& data) {
		auto it = data.begin();
		m_data = new T[size()];
		for (size_t i = 0; i < size(); i++) {
			m_data[i] = *it;
			*it++;
		}
	};

	Vector(T * array)
	{
		m_data = array;
	}

	Vector(const Vector& v)
	{
		m_data = new T[size()];
		for (size_t i = 0; i < size(); i++) {
			m_data[i] = v.m_data[i];
		}
	}
	template<typename Left, typename Op, typename Right>
	Vector(Expression<Left, Op, Right, T> e)
	{
		this->m_data = e.calc(sizeL);
	}

	T & operator[](int i) const {
		return m_data[i];
	}

	

	/**operators */
	struct Add {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l + r;
		}
	};

	/**operators */
	struct Subtraction {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l - r;
		}
	};

	/**operators */
	struct PMultiplication {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l * r;
		}
	};

	/**operators */
	struct PDivision {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l / r;
		}
	};

	bool operator==(const Vector b) const {
		if (this->size() == b.size())
		{
			for (size_t i = 0; i < this->size(); i++)
			{
				T temp1 = (*this)[i];
				T temp2 = b[i];
				if ((*this)[i] != b[i])
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator<<(ostream& out, Vector<T, sizeL> vector) {
		vector.print(out);
		return out;
	}

	template<typename Left, typename Op, class Right >
	friend bool operator==(Expression<Left, Op, Right, T> & l, const Vector<T, sizeL> & r) {

		return (Vector<T, sizeL>(l.calc(sizeL)) == r);

	}


	Expression<Vector<T, sizeL>, Add, T, T>  operator+(const T & r) const {
		Expression< Vector<T, sizeL>, Add, T, T> e((*this), r);
		return e;
	}


	template<typename Left, class Right>
	friend Expression<Left, Add, Right, T> operator+(const Left& l, const Right & r) {
		Expression<Left, Add, Right, T>  e(l, r);
		return e;
	}

	Expression<Vector<T, sizeL>, Subtraction, T, T>  operator-(const T & r) const {
		Expression< Vector<T, sizeL>, Subtraction, T, T> e((*this), r);
		return e;
	}


	template<typename Left, class Right>
	friend Expression<Left, Subtraction, Right, T> operator-(const Left& l, const Right & r) {
		Expression<Left, Subtraction, Right, T>  e(l, r);
		return e;
	}

	Expression<Vector<T, sizeL>, PMultiplication, T, T>  operator*(const T & r) const {
		Expression< Vector<T, sizeL>, PMultiplication, T, T> e((*this), r);
		return e;
	}


	template<typename Left, class Right>
	friend Expression<Left, PMultiplication, Right, T> operator*(const Left& l, const Right & r) {
		Expression<Left, PMultiplication, Right, T>  e(l, r);
		return e;
	}

	Expression<Vector<T, sizeL>, PDivision, T, T>  operator/(const T & r) const {
		Expression< Vector<T, sizeL>, PDivision, T, T> e((*this), r);
		return e;
	}


	template<typename Left, class Right>
	friend Expression<Left, PDivision, Right, T> operator/(const Left& l, const Right & r) {
		Expression<Left, PDivision, Right, T>  e(l, r);
		return e;
	}
};



