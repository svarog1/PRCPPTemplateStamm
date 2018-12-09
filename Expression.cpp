#pragma once
#include <memory>
#include "pch.h"
#include <iostream>

using namespace std;

template<class List, typename Op, typename T> class Expression {
	const List& m_left;
	const List & m_right;
public:

	Expression(const List& l, const List& r) : m_left{ l }, m_right{ r } {
		m_left.print();
	}

	int size() const {
		return m_left.size();
	}

	T operator[](int i) const {
		return Op::template apply<T>(m_left[i], m_right[i]);
	}

	List& calc(int size)
	{
		T *array = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			array[i] = (*this)[i];
		}
		List * result = new List(array);
		return (*result);
	}


};



