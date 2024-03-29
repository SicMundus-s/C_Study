﻿#include <iostream>

#include <iostream>


#include <iostream>
#include <chrono> // для функций из std::chrono

template <class T>
class DynamicArray
{
private:
	T* m_array;
	int m_length;

public:
	DynamicArray(int length)
		: m_array(new T[length]), m_length(length)
	{
	}

	~DynamicArray()
	{
		delete[] m_array;
	}

	// Конструктор копирования
	DynamicArray(const DynamicArray& arr) = delete;

	// Оператор присваивания копированием
	DynamicArray& operator=(const DynamicArray& arr) = delete;

	// Конструктор перемещения
	DynamicArray(DynamicArray&& arr)
		: m_length(arr.m_length), m_array(arr.m_array)
	{
		arr.m_length = 0;
		arr.m_array = nullptr;
	}

	// Оператор присваивания перемещением
	DynamicArray& operator=(DynamicArray&& arr)
	{
		if (&arr == this)
			return *this;

		delete[] m_array;

		m_length = arr.m_length;
		m_array = arr.m_array;
		arr.m_length = 0;
		arr.m_array = nullptr;

		return *this;
	}

	int getLength() const { return m_length; }
	T& operator[](int index) { return m_array[index]; }
	const T& operator[](int index) const { return m_array[index]; }

};

class Timer
{
private:
	// Используем псевдонимы типов для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

// Возвращаем копию arr со значениями, умноженными на 2
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int>& arr)
{
	DynamicArray<int> dbl(arr.getLength());
	for (int i = 0; i < arr.getLength(); ++i)
		dbl[i] = arr[i] * 2;

	return dbl;
}

int main()
{
	Timer t;

	DynamicArray<int> arr(1000000);

	for (int i = 0; i < arr.getLength(); i++)
		arr[i] = i;

	arr = cloneArrayAndDouble(arr);

	std::cout << t.elapsed();
}