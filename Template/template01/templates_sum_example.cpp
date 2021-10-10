#include <iostream>

template <typename T, typename U>
T sum(T const* pArray, int const ELEMENTS)
{
    T sum = 0;

    for (int index = 0; index < ELEMENTS; index++)
    {
        sum += pArray[index] * pArray[index];
    }

    return sum;
}


int main()
{
    //size_t numElements = 4;
    int const ELEMENTS = 10;
    int intArray[] = { 1,2,3,4,5,6,7,8,9,10 };

    float floatArray[] =
    { 1.1f,2.2f,3.3f,4.4f,5.5f,6.6f,7.7f,8.8f,9.9f,10.1f };

    // sum<int>(....)
    //std::cout << "Sum of squares of integer array: " <<
    //    sum(intArray, ELEMENTS) << std::endl;

    //std::cout << "Sum of squares of float array: " <<
    //    sum(floatArray, ELEMENTS) << std::endl;

    std::cin.get();
}
