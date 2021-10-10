#include "checkWord.h"
#include <stack>

bool checkWord::checkForNumbers(std::string number)
{
    bool allAreLetters = true;
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] <= 64) // check for control characters , special characters and numbers
        {
            allAreLetters = false;
            return false;
        }
    }
    return allAreLetters;
}

bool checkWord::checkForSpecialLetters(std::string specialCharacter)
{
    bool allAreLetters = true;
    for (int i = 0; i < specialCharacter.size(); i++)
    {
        if (specialCharacter[i] >= 91 && specialCharacter[i] <= 96) // check for special characters 
        {
            allAreLetters = false;
            return false;
        }
        else if (specialCharacter[i] >= 123) // check for special characters 
        {
            allAreLetters = false;
            return false;
        }
    }
    if (allAreLetters == true)
    {
        return true;
    }
}

bool checkWord::checkForLettersOnGrid(std::string playerWord, Grid t_grid)
{
    //Refer to ASCII table for refrence 

    std::string copyWord = playerWord;
    std::string allowedLetters;

    for (int j = 0; j < 16; j++)
    {
        allowedLetters = allowedLetters + t_grid.passRandomisedValues(j);
    }

    int numberOfCorrect = 0; // if the number of this variable is the same as what the player put in , the answer is allow

    for (int i = 0; i < copyWord.size(); i++)
    {
        for (int counter = 0; counter < allowedLetters.size(); counter++) // this for loop check if the letter that the payer put in is are available on the grid
        {
            if (copyWord[i] == allowedLetters[counter] || (copyWord[i] == (allowedLetters[counter] + 32))) //Plus 32 incase the player use small letters instead of capital letters
            {
                //std::cout << "correct" << std::endl;
                numberOfCorrect++; // as long as the word that the player put in match one of the letter on the grid , this counter will go up
                break; // as soon as the word that the player put in match with any of the one in the array , it will break and move to the next letter 
            }
            else if (copyWord[i] != allowedLetters[counter] || (copyWord[i] != (allowedLetters[counter] + 32)))
            {
                //std::cout << " wrong" << std::endl;
                continue; // continue if the letter is not available during the current loop , as the letter might be available later on in the array
            }
        }
    }

    if (numberOfCorrect == playerWord.size())// if the number of correct is the same as the number of player put in means that every single letter that the player put in is allow
    {
        return true;
    }
    else if (numberOfCorrect != playerWord.size())
    {
        return false;
    }
}

bool checkWord::checkForLettrsOnGridString(std::string playerWord, std::string wordFromGrid)
{
    std::string copyWord = playerWord;
    std::string allowedLetters  = wordFromGrid;
    int numberOfCorrect = 0;

    for (int i = 0; i < copyWord.size(); i++)
    {
        for (int counter = 0; counter < allowedLetters.size(); counter++) // this for loop check if the letter that the payer put in is are available on the grid
        {
            if (copyWord[i] == allowedLetters[counter] || (copyWord[i] == (allowedLetters[counter] + 32))) //Plus 32 incase the player use small letters instead of capital letters
            {
                //std::cout << "correct" << std::endl;
                numberOfCorrect++; // as long as the word that the player put in match one of the letter on the grid , this counter will go up
                break; // as soon as the word that the player put in match with any of the one in the array , it will break and move to the next letter 
            }
            else if (copyWord[i] != allowedLetters[counter] || (copyWord[i] != (allowedLetters[counter] + 32)))
            {
                //std::cout << " wrong" << std::endl;
                continue; // continue if the letter is not available during the current loop , as the letter might be available later on in the array
            }
        }
    }

    if (numberOfCorrect == playerWord.size())// if the number of correct is the same as the number of player put in means that every single letter that the player put in is allow
    {
        return true;
    }
    else if (numberOfCorrect != playerWord.size())
    {
        return false;
    }
}

bool checkWord::checkAllConditions(std::string playerWord, Grid t_grid)
{
    bool noNumber = checkForNumbers(playerWord);
    bool noSpecialChar = checkForSpecialLetters(playerWord);
    bool allConditionIsMet = false;

    if (noNumber == true && noSpecialChar == true)
    {
        allConditionIsMet = checkForLettersOnGrid(playerWord, t_grid);
    }
    
    return allConditionIsMet;
}

void checkWord::invalidWord()
{
    std::cout << "illegal word (not on grid, has special characters or is a repeat word)" << std::endl;
    std::cout << "please try again" << std::endl;
    std::cout << "(Enter anything to continue)" << std::endl;
    std::cin >> confirmation;
}
