#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "RenderScore.h"

class StoreUsedWords
{
public:
	const static int MAX_WORDS = 30;
	int index;
	std::string t_words[MAX_WORDS];

	std::vector<std::string> m_words;

	void addNewWordToArray(std::string t_word);
	bool checkIfRepeatWord(std::string t_word);
	
	void resetArray();

	StoreUsedWords(){
	m_words = {"","","","","",
			   "","","","","",
			   "","","","","",
			   "","","","","",
			   "","","","","",              
			   "","","","",""};
	}
};

