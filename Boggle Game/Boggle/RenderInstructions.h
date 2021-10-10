#pragma once
#include <iostream>
class Instructions
{
private:
	std::string m_instruc[5] = { "You have 180 seconds (shown by the countdown timer) to find as many words as you can in the grid.\nNo letter cube may be used more than once within a single word.",
		"Type your words into the box below the grid.\nIt does not matter whether you use upper or lower case letters.",
		"Press Enter after each word. Words need to be at least 3 letters long. \nScore will be calculated automatically as you submit each word." ,
		"When the time is up, your current score and your all time high score will be displayed.",
		"\nPlease choose an option:\n 0-Exit Game   1-Start Game"};
public:
	void displayInstruc();
};