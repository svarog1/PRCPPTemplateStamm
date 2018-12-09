#pragma once
#include <memory>
#include "pch.h"
#include <iostream>

using namespace std;



template<class Left, typename Op, class Right, class T> class Expression {
	const Left& m_left;
	const Right & m_right;
public:
	//Only in c++ 17 or later. (if constexpr)
	constexpr T operator[](int i) const {
		if constexpr (std::is_arithmetic<Right>{}) { // std::is_same_v<Right, T>) {
			return Op::template apply<T>(m_left[i], m_right);
		}
		else if constexpr (std::is_arithmetic<Left>{}) { // std::is_same_v<Right, T>) {
			return Op::template apply<T>(m_left, m_right[i]);
		}
		else {
			return Op::template apply<T>(m_left[i], m_right[i]);
		}
	}

	Expression(const Left& l, const Right& r) : m_left{ l }, m_right{ r } {
	}


	int size() const {
		return m_left.size();
	}



	constexpr auto& calc(int size) {
		if constexpr (std::is_arithmetic<Left>{}) { // std::is_same_v<Right, T>) {
			T *array = new T[size];
			for (size_t i = 0; i < size; i++)
			{
				array[i] = (*this)[i];
			}
			Right * result = new Right(array);
			return (*result);
		}
		else {
			T *array = new T[size];
			for (size_t i = 0; i < size; i++)
			{
				array[i] = (*this)[i];
			}
			Left * result = new Left(array);
			return (*result);
		}
	}

	/*auto& calc(int size)
	{
		T *array = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			array[i] = (*this)[i];
		}
		Left * result = new Left(array);
		return (*result);
	}*/

};

