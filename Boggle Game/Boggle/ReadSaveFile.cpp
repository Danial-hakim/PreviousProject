#include "ReadSaveFile.h"

void ReadSaveFile::readSaveFile(Score &m_score)
{
	std::string currentFile = "highScore.txt";;
	//std::string aMessage = "Function is being called";

	std::ifstream inputFile;

	inputFile.open(currentFile); 

	if (inputFile.is_open())
	{
		inputFile >> m_score.m_highestPlayerScore;
		
		inputFile.close(); 

		//aMessage = "Reading succesful";
	}
	else
	{
		//aMessage = "File reading error occurred";
	}

	//std::cout << aMessage;
}
