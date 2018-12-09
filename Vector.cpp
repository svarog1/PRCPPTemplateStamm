#pragma once
#include <memory>
#include "pch.h"
#include <iostream>
#include "C:\Users\santi\source\repos\PRCPPTemplatesStamm\Expression.cpp"
#include <cstring>

using namespace std;



template<class T, const int sizeL>
class Vector {
private:
	T * m_data;

public:

	T getValue(int i) {
		return data[i];
	}

	int size() const {
		return sizeL;
	}

	void temp()
	{
		m_data[0] = 100;
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

	T operator[](int i) const {
		return m_data[i];
	}

	/*Vector operator[](int i) const {
		return m_data[i];
	}*/

	void print() const
	{
		cout << "Start: \n";
		for (size_t i = 0; i < size(); i++)
		{
			T t = m_data[i];
			cout << m_data[i] << " : ";

		}
		cout << "\n";
	}

	bool operator==(const Vector<T, sizeL>& b) const {
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

	Vector& operator+(const Vector<T, sizeL>& b) const {
		Expression<Vector, Add, Vector, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator-(const Vector<T, sizeL>& b) const {
		Expression<Vector, Subtraction, Vector, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator*(const Vector<T, sizeL>& b) const {
		Expression<Vector, PMultiplication, Vector, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator/(const Vector<T, sizeL>& b) const {
		Expression<Vector, PDivision, Vector, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator+(const T & b) const {
		Expression<Vector, Add, T, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator-(const T & b) const {
		Expression<Vector, Subtraction, T, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator*(const T& b) const {
		Expression<Vector, PMultiplication, T, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator/(const T& b) const {
		Expression<Vector, PDivision, T, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	friend Vector& operator+(T r, const Vector<T, sizeL>& l) {
		return l + r;
	}

	friend Vector& operator-(T r, const Vector<T, sizeL>& l) {
		Expression<T, Subtraction, Vector, T>  e(r, l);
		Vector& result = e.calc(sizeL);
		return result;
	}

	friend Vector& operator*(T r, const Vector<T, sizeL>& l) {
		return l * r;
	}

	friend Vector& operator/(T r, const Vector<T, sizeL>& l) {
		Expression<T, PDivision, Vector, T>  e(r, l);
		Vector& result = e.calc(sizeL);
		return result;
	}




	struct Add {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l + r;
		}
	};

	struct Subtraction {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l - r;
		}
	};

	struct PMultiplication {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l * r;
		}
	};

	struct PDivision {
		template<typename T>
		static T apply(const T l, const T r)
		{
			return l / r;
		}
	};


	//Start for Skalarprodukt
	struct ScalarStruct
	{
	public:
		Vector m_v;
		ScalarStruct(const Vector& v) :m_v(v) {}

		Vector& operator*() const {
			return m_v;
		}
	};

	ScalarStruct operator*() const {
		return ScalarStruct((*this));
	}
	//Berechnet das Skalarprodukt
	friend T operator*(const Vector<T, sizeL>& lhs, const ScalarStruct& rhs)
	{
		Vector& result = rhs.m_v * lhs;
		result.print();
		T value;
		for (size_t i = 0; i < result.size(); i++)
		{
			if (i == 0)
			{
				value = result[i];
			}
			else
			{
				value += result[i];
			}
		}
		return value;
	}
	//End for Skalarprodukt
};



