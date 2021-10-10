#include <iostream>
#include <array>
#include <vector>
#include <time.h>
#include <algorithm> // to use std::for_each
#include <string>

// Functors is a function object 
// A class tht overload the function call operator

class sum
{
public:
	void operator()(int t_x) // function call operator 
	{
		m_sum += t_x;
	}

private:
	int m_sum{ 0 };
};

class totalCharacNum
{
public:
	void operator()(std::string t_x)
	{
		m_total += t_x.length();
	}
private:
	int m_total{ 0 };
};

class compareByLength
{
public:
	bool operator()(std::string& t_str1, std::string& t_str2)
	{
		return t_str1.length() < t_str2.length();
	}
};

int main1()
{
	//==========================================
	//Functors example 

	sum s;

	std::vector<int> v = { 1,2,3,4 };
	s = std::for_each(v.begin(), v.end(), s);

	std::vector<std::string> y = { "aaa","z","yy","bbb" };
	std::sort(y.begin(), y.end(), compareByLength());
	//==========================================
	//Functors exercise

	totalCharacNum t;

	std::vector<std::string> vv = { "aa","bbb","c","abcd" };
	t = std::for_each(vv.begin(), vv.end(), t);
	//==========================================
	//lambda

	int x = 0;
	//mutable - means this lambda can write to any external variables
	//[=] means capture by value
	//[&] means capture by ref

	auto func = [=]() mutable //  capture any external variable
	{
		x = 10;
		std::cout << x;
	};

	func();
	compareByLength c2;

	std::vector<std::string> v2 = { "aaa","z","yy","bbb" };
	std::sort(v2.begin(), v2.end(), [](std::string& t_str1, std::string& t_str2)
		{
			return t_str1.length() < t_str2.length();
		}
	);
	//==========================================
	//Exerise for Lambda

	int total;

	std::for_each(v2.begin(), v2.end(), [&](std::string& t_str1)
		{
			total += t_str1.length();

			return total;
		}
	);
	//==========================================
	//Vector example

	std::vector<int> v3;
	v3.push_back(1);
	//Read the capacity 
	int cap = v3.capacity();
	//Create an iterator to start of v3
	std::vector<int>::iterator it = v3.begin();
	//Trigger memory reallocation
	v3.push_back(2);
	//It is now invalid 
	
	//==========================================
	return 1;
}