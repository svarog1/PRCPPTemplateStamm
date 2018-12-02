#pragma once
#include <memory>
#include "pch.h"
#include <iostream>

using namespace std;



template<class T, size_t sizeL> class Vector {
public:
	unique_ptr<T[sizeL]> m_array;
	size_t m_size;

	Vector(const std::initializer_list<T>& data) {
		size_t s = __min(data.size(), sizeL);
		auto it = data.begin();
		for (size_t i = 0; i < s; i++) {
			this->at(i) = *it++;
		}
		m_size = sizeL;
	}

	Vector(T[]) :m_array(new T[sizeL]), m_size(sizeL)
	{
	
	};



	Vector operator-(const Vector& b) {
		Vector subtraktion = new Vector(b.m_size);
		if (this->m_size == b.m_size) {

			for (size_t i = 0; i < this->m_size; i++) {

				subtraktion.m_array[i] = this->m_array[i] - b.m_array[i];
			}
		}
		else
		{
			throw "Vektoren nicht gleich lang.";
		}
		return subtraktion;
	}

	Vector operator+(const Vector& b) {

		Vector sum = new Vector(b.m_size);

		if (this->m_size == b.m_size) {

			for (size_t i = 0; i < this->m_size; i++) {

				sum.m_array[i] = this->m_array[i] + b.m_array[i];
			}
		}
		else
		{
			throw "Vektoren nicht gleich lang.";
		}
		return sum;

	}

	Vector operator* (const Vector& b) {
		Vector produkt(b.m_size);
		if (this->m_size == b.m_size) {
			for (size_t i = 0; i < this->m_size; i++) {

				produkt.m_array[i] = this->m_array[i] * b.m_array[i];
			}
		}
		else
		{
			throw "Vektoren nicht gleich lang.";
		}
		return produkt;
	}

	Vector operator/(const Vector& b) {
		Vector division = new Vector(b.m_size);
		if (this->m_size == b.m_size) {
			for (size_t i = 0; i < this->m_size; i++) {
				if (b.m_array[i] != 0) {
					division.m_array[i] = this->m_array[i] * b.m_array[i];
				}
				else {
					throw "Division durch 0";
				}
			}
		}
		else
		{
			throw "Vektoren nicht gleich lang.";
		}
		return division;
	}

	Vector SkalarAddition(T skalar) {
		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = this->m_array[i] + skalar;
		}
		return this;
	}

	Vector SkalarSubtraktionLinks(T skalar) {
		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = this->m_array[i] - skalar;
		}
		return this;
	}

	Vector SkalarSubtraktionRechts(T skalar) {
		for (size_t i = 0; i < this->m_size; i++) {

			this->m_array[i] = skalar - this->m_array[i];
		}
		return this;
	}

	Vector SkalarMultiplikation(T skalar) {
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;
		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = this->m_array[i] * skalar;
		}
		return this;
	}

	Vector SkalarDivisionRechts(T skalar) {
		if (skalar != 0) {
			for (size_t i = 0; i < this->m_size; i++) {
				this->m_array[i] = this->m_array[i] / skalar;
			}
		}
		return this;
	}

	Vector SkalarDivisonLinks(T skalar) {
		for (size_t i = 0; i < this->m_size; i++) {
			if (this->m_array[i] != 0) this->m_array[i] = skalar / this->m_array[i];
		}
		return this;
	}

	T Skalarprodukt(const Vector& b) {
		T skalarprodukt = new Vector(b.m_size);
		for (size_t i = 0; i < this->m_size; i++) {
			skalarprodukt.m_array[i] = this->m_array[i] * b.m_array[i];
		}
		return skalarprodukt;
	}

	//friend bool operator== ( Vector b,  Vector a)
	//{
	//	if (a.m_size != b.m_size)
	//	{
	//		return false;
	//	}
	//	for (size_t i = 0; i < length; i++)
	//	{
	//		if (a[i] != b[i])
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//}

	//friend bool operator== (Vector a)
	//{
	//	if (a.m_size != b.m_size)
	//	{
	//		return false;
	//	}
	//	for (size_t i = 0; i < length; i++)
	//	{
	//		if (a[i] != b[i])
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//}
};