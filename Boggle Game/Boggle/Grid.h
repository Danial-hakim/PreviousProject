#pragma once
#include <time.h>
#include <iostream>

class Grid
{
private:

	//the letter from each die that has been randomised
	std::string chosenLetters[16];

	//the cell number that has been randomised
	int rand[16];

	//dice configurations used in original boggle
	const std::string DIE[16][6] = { { "R","I","F","O","B","X"}, { "I","F","E","H","E","Y" },
{ "D","E","N","O","W","S"},{ "U","T","O","K","N","D"}, { "H","M","S","R","A","O"},
{ "L","U","P","E","T","S"},{ "A","C","I","T","O","A"}, { "Y","L","G","K","U","E"},
{ "Qu","B","M","J","O","A"}, { "E","H","I","S","P","N"}, { "V","E","T","I","G","N"},
{ "B","A","L","I","Y","T"}, { "E","Z","A","V","N","D"}, { "R","A","L","E","S","C"},
{ "U","W","I","L","R","G"}, { "P","A","C","E","M","D"} };

public:

	//randomises the letters according to commonly used dice configuration
	void randomiseLetters();

	//passes the value that was randomised
	std::string passRandomisedValues(int t_arrayCell);

	//passes the constant letter from the grid
	std::string passConstantValues(int t_array, int t_arrayCell);

	//passes the number which was used to randomise letter
	int passCellNumber(int t_arrayCell);
};

