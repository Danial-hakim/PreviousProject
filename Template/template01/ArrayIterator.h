#pragma once

template <typename Array>
class ArrayIterator
{
public:
	using ValueType = Array::ValueType;
public:
	ArrayIterator(ValueType* t_element) : m_element(t_element)
	{}

	ValueType& operator *() const
	{
		return *m_element;
	}

	// Prefix ++
	ArrayIterator& operator ++()
	{
		m_element++;
		return *this;
	}

	// Postfix ++	
	ArrayIterator operator ++(int)
	{
	    ArrayIterator temp(m_element);
		m_element++;
		return temp;
	}

	bool operator !=(ArrayIterator& t_other) const
	{
		return m_element != t_other.m_element;
	}

private:
	ValueType* m_element;
};