#include "SaveToFile.h"

void SaveToFile::writeToSaveFile(Score &m_score)
{
	std::ofstream outputFile;
	outputFile.open("highScore.txt"); // creates or replaces the file

	// writes to the file
	outputFile << m_score.m_playerScore << "\n";

	outputFile.close(); 
	//std::cout << std::endl << "Write successful" << std::endl;
}
