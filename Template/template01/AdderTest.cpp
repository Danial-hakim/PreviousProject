#include <iostream>
#include <array>
#include <vector>
#include <time.h>
#include <algorithm> // to use std::for_each
#include <string>

template<typename T, int size> // size has to be int 
T scalarProduct(std::array<T, size>& t_arr , std::array<T, size>& arr) //Q1
{
	T answer =
		t_arr[0] * arr[0] +
		t_arr[1] * arr[1] +
		t_arr[2] * arr[2];

	return answer;
}

template<typename M, int size>
std::pair<M,M> minMax(std::array<M, size>& t_vector) //Q2
{
	std::pair<M,M> answer;

	answer.first = t_vector[0]; //minimum value
	answer.second = t_vector[0]; //maximum value

	for ( int i = 1 ; i < size ; i++ )
	{
		if (answer.first < t_vector[i])
		{
			answer.first = t_vector[i]; 
		}
		if (answer.second > t_vector[i])
		{
			answer.second = t_vector[i]; 
		}
	}
	
	return answer;
}

class record
{
public:

	int count;
	int price;
};

enum class sortBy
{
	Stock,
	Price
};

template<typename T>
class CompareRecords
{
public:

	CompareRecords(T compare)
	{
		m_compare = compare;
	}

	bool operator()(record& t_record, record& t_record2)
	{
		if (m_compare == sortBy::Stock)
		{
			return t_record.count < t_record2.count;
		}
		else
		{
			return t_record.price < t_record2.price;
		}
	}

private:
	T m_compare;
};
int main()
{
	//=================================================
	//Q1
	std::array<float, 3> vecOne{ 1.0f,2.4f,3.5f };
	std::array<float, 3> VecTwo{ 1.2f,2.2f,3.9f };

	scalarProduct<float, 3>(vecOne, VecTwo);
	//=================================================
	//Q2
	std::array<float, 3> VecThree{ 1.2f,2.2f,3.9f };

	std::array<std::string, 3> vecFour{ "middleee","short","longesttttttttt" };

	minMax(VecThree);

	minMax(vecFour);
	//=================================================
	//Q3
	record r1, r2, r3;
	r1.count = 3;
	r2.count = 1;
	r3.count = 2;

	r1.price = 50;
	r2.price = 10;
	r3.price = 30;

	std::vector<record> records = { r3,r2,r1 };
	std::sort(records.begin(), records.end(),CompareRecords<sortBy>(sortBy::Stock));

	//=================================================
	//Q4
	std::vector<int> randNumVec;
	int randNum;

	randNumVec.capacity();

	for (int i = 0; i < 20; i++)
	{
		randNum = (rand() % 9) + 1;
		randNumVec.push_back(randNum);
	}
}


