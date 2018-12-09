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
		v.print();
		m_data = new T[size()];
		for (size_t i = 0; i < size(); i++) {
			m_data[i] = v.m_data[i];
		}
		print();
	}

	T operator[](int i) const {
		return m_data[i];
	}

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
		Expression<Vector, Add, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator-(const Vector<T, sizeL>& b) const {
		Expression<Vector, Subtraction, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator*(const Vector<T, sizeL>& b) const {
		Expression<Vector, PMultiplication, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}

	Vector& operator/(const Vector<T, sizeL>& b) const {
		Expression<Vector, PDivision, T>  e(*this, b);
		Vector& result = e.calc(sizeL);
		return result;
	}


	struct Add {
		template<typename T>
		static T apply(T l, T r)
		{
			return l + r;
		}
	};

	struct Subtraction {
		template<typename T>
		static T apply(T l, T r)
		{
			return l - r;
		}
	};

	struct PMultiplication {
		template<typename T>
		static T apply(T l, T r)
		{
			return l * r;
		}
	};

	struct PDivision {
		template<typename T>
		static T apply(T l, T r)
		{
			return l / r;
		}
	};

};
