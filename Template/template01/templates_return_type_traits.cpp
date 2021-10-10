#include <iostream>

template<typename AverageType, typename SumType>
struct item_return { typedef AverageType type; };

template<typename AverageType, typename SumType>
typename item_return<AverageType, SumType>::type sum(SumType *t_array, int const ELEMENTS)
{ 
	SumType sum = 0;

	for (int i = 0; i < ELEMENTS; i++)
	{
		sum += t_array[i];
	}

	return static_cast<AverageType> (sum) / ELEMENTS; 
}



int main()
{
	int iArray[] = { 1, 2, 3, 4 };
	float average = sum<float, int>(iArray, 4);
	std::cin.get();
}
