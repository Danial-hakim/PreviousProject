#include <iostream>

template <typename T, int size>
class Array
{
public:
    void set(T item, int index)
    {
        m_array[index] = item;
    }

    T get(int index)
    {
        return m_array[index];
    }
private:
    T m_array[size];
};


int main() {

    Array<int, 5> intArray;
    Array<float, 5> floatArray;

    int i;
    float f;
    for (i = 0, f = 0; i < 5; i++, f += 1.1f)
    {
        intArray.set(i, i);
        floatArray.set(f, i);
        std::cout << "intArray.get(" << i << ") = "
                  << intArray.get(i) << std::endl;

        std::cout << "floatArray.get(" << i << ") = "
                  << floatArray.get(i) << std::endl;
    }
    std::cin.get();
}
