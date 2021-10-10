#pragma once
#include <stdexcept>      // for std::out_of_range
#include "ArrayIterator.h"


template<typename T> 
class Array 
{
public:
	using ValueType = T;
	using Iterator = ArrayIterator<Array<T>>;
public:
	Array(int t_size) : m_size(t_size)
	{
		m_array = new ValueType[t_size];
	}
	~Array()
	{
		delete[] m_array;
	}

	// Overloaded index operator
	ValueType & operator[](int t_index)
	{
		if (t_index < m_size)
		{
			return m_array[t_index];
		}
		else
		{
			throw std::out_of_range("Bad index");
		}
	}

	Iterator begin() const
	{
		return Iterator(m_array);
	}

	Iterator end() const
	{
		return Iterator(m_array + m_size);
	}
	

private:
	int m_size;
	T* m_array;
};