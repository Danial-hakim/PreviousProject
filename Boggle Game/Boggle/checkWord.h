#pragma once
#include <iostream>
#include "Grid.h"

class checkWord
{

private: 
    // used to process invaild words
    std::string confirmation = "";
public:
    checkWord() {};
    bool checkForSpecialLetters(std::string specialCharacter);
    bool checkForNumbers(std::string number);
    bool checkForLettersOnGrid(std::string playerWord, Grid t_grid);
    bool checkForLettrsOnGridString(std::string playerWord, std::string wordFromGrid);
    bool checkAllConditions(std::string playerWord, Grid t_grid);
    void invalidWord();
};