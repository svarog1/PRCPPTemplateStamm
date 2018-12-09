#pragma once
#include <memory>
#include "pch.h"
#include <iostream>

using namespace std;


/**This class works only in c++ 17 or later. (if constexpr) */

template<class Left, typename Op, class Right, class T> class Expression {
	const Left& m_left;
	const Right & m_right;
public:



	Expression(const Left& l, const Right& r) : m_left{ l }, m_right{ r } {
	}


	int size() const {
		return m_left.size();
	}


	constexpr T operator[](int i) const
	{

		/**Using when Right is a arithmetic (int, bool .....) */
		if constexpr (std::is_arithmetic<Right>{})
		{
			/**Op need to be a struct wiht a function apply. This ar defined in Vector (Add, Subtraction)*/
			return Op::template apply<T>(m_left[i], m_right);
		}
		/**Using when Left is a arithmetic (int, bool .....) */
		else if constexpr (std::is_arithmetic<Left>{})
		{
			return Op::template apply<T>(m_left, m_right[i]);
		}
		else {
			return Op::template apply<T>(m_left[i], m_right[i]);
		}
	}

	constexpr auto& calc(int size) {
		/**Using when Left is a arithmetic (int, bool .....) */
		if constexpr (std::is_arithmetic<Left>{})
		{
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

	};

};