#include "pch.h"
#include "../Boggle/Timer.cpp"
#include "../Boggle/Scoring.cpp"
#include "../Boggle/Grid.cpp"
#include "../Boggle/checkWord.cpp"
#include "../Boggle/StoreUsedWords.cpp"
#include "../Boggle/SaveToFile.cpp"
#include "../Boggle/ReadSaveFile.cpp"

TEST(Timer, TimerStart)
{
	Timer time;
	time.start();

	while (time.elapsedSeconds() <= 2)
	{
		time.m_EndTime = std::chrono::system_clock::now();
	}
 
	EXPECT_TRUE(time.m_StartTime < time.m_EndTime);
}

TEST(Timer, Timer5000MillisecondsElapsed)
{
	Timer time;
	time.start();

	while (time.elapsedMilliseconds() < 5000)
	{
		// game loop here...
	}

	time.stop();

	EXPECT_EQ(5000, time.elapsedMilliseconds());
}

TEST(Timer, Timer10SecondsElapsed)
{
	Timer time;

	time.start();

	while (time.elapsedSeconds() < 10)
	{
		// game loop here...
	}

	time.stop();

	EXPECT_EQ(10, time.elapsedSeconds());
}

TEST(Timer, ConvertToCountDown)
{
	Timer time;

	time.setGameTime(10);

	time.start();

	while (time.elapsedSeconds() < 1)
	{
		// game loop here...
	}

	time.stop();

	EXPECT_EQ(9, time.convertToCountDown());
}

TEST(Grid, CheckCorrectRead0)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(0);
	std::string configuration = grid.passConstantValues(0, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(0));
}
TEST(Grid,CheckCorrectRead3)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(3);
	std::string configuration = grid.passConstantValues(3, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(3));
}

TEST(Grid, CheckCorrectRead5)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(5);
	std::string configuration = grid.passConstantValues(5, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(5));
}

TEST(Grid, CheckCorrectRead7)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(7);
	std::string configuration = grid.passConstantValues(7, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(7));
}

TEST(Grid, CheckCorrectRead9)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(9);
	std::string configuration = grid.passConstantValues(9, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(9));
}

TEST(Grid, CheckCorrectRead10)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(10);
	std::string configuration = grid.passConstantValues(10, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(10));
}

TEST(Grid, CheckCorrectRead15)
{
	Grid grid;

	grid.randomiseLetters();

	int cell = grid.passCellNumber(15);
	std::string configuration = grid.passConstantValues(15, cell);

	EXPECT_EQ(configuration, grid.passRandomisedValues(15));
}
TEST(checkWord, checkForNumber)
{
	std::string number = "88";

	checkWord numberChecking;

	bool thereIsNumber = numberChecking.checkForNumbers(number);

	EXPECT_FALSE(thereIsNumber);
}

TEST(checkWord, checkForLargeNumber)
{
	std::string numbers = "883284732508792744";

	checkWord numberChecking;

	bool thereIsLargeNumber = numberChecking.checkForNumbers(numbers);

	EXPECT_FALSE(thereIsLargeNumber);
}

TEST(checkWord, checkForNumberInBetween)
{
	std::string numbersInBetween = "asd2d";

	checkWord numberChecking;

	bool thereIsNumber = numberChecking.checkForNumbers(numbersInBetween);

	EXPECT_FALSE(thereIsNumber);
}

TEST(checkWord, checkForSpecialChar)
{
	std::string specialChar = "?/}";

	checkWord specialCharChecking;

	bool thereIsSpecialChar = specialCharChecking.checkForSpecialLetters(specialChar);

	EXPECT_FALSE(thereIsSpecialChar);
}

TEST(checkWord, checkForSpecialCharInBetween)
{
	std::string specialCharInBetween = "adl?}jh";

	checkWord specialCharChecking;

	bool thereIsSpecialChar = specialCharChecking.checkForSpecialLetters(specialCharInBetween);

	EXPECT_FALSE(thereIsSpecialChar);
}

TEST(checkWord, checkForSpaceInBetween)
{
	std::string specialCharInBetween = "ad jh";

	checkWord specialCharChecking;

	bool thereIsSpecialChar = specialCharChecking.checkForNumbers(specialCharInBetween); // space ASCII is 32

	EXPECT_FALSE(thereIsSpecialChar);
}

TEST(checkWord, checkIfLettersIsOnGrid) // player put all small letter
{
	std::string wordFromPlayer = "qwerty";
	
	std::string wordOnGrid = "QWERTY";

	checkWord checkForLettersOnGrid;

	bool isLettersAllowed = checkForLettersOnGrid.checkForLettrsOnGridString(wordFromPlayer,wordOnGrid);

	EXPECT_TRUE(isLettersAllowed);
}

TEST(checkWord, smallLettersFromPlayer) // player mix both capital and small letters
{
	std::string wordFromPlayer = "QwErTy";

	std::string wordOnGrid = "QWERTY";

	checkWord checkForLettersOnGrid;

	bool isLettersAllowed = checkForLettersOnGrid.checkForLettrsOnGridString(wordFromPlayer, wordOnGrid);

	EXPECT_TRUE(isLettersAllowed);
}

TEST(checkWord, lettersNotOnGrid) // player use letter that are not on the grid
{
	std::string wordFromPlayer = "qwerty";

	std::string wordOnGrid = "POLO";

	checkWord checkForLettersOnGrid;

	bool isLettersAllowed = checkForLettersOnGrid.checkForLettrsOnGridString(wordFromPlayer, wordOnGrid);

	EXPECT_FALSE(isLettersAllowed);
}

TEST(checkWord, someLettersNotOnGrid) // player use some letters that are available on the grid and some letters that are not 
{
	std::string wordFromPlayer = "qwerPos";

	std::string wordOnGrid = "POLO";

	checkWord checkForLettersOnGrid;

	bool isLettersAllowed = checkForLettersOnGrid.checkForLettrsOnGridString(wordFromPlayer, wordOnGrid);

	EXPECT_FALSE(isLettersAllowed);
}

 //<summary>
 //Tests the score if word is 2 or less than 2 letters long
 //</summary>
 //<param name=""></param>
 //<param name=""></param>
TEST(Score, lessThan2Letters) 
{
	Score player_score;

	int tempScore = 0;

	std::string tempWord = "he";

	player_score.m_playerScore = 0;

	player_score.m_calculateScore(tempWord);

	tempScore = player_score.m_playerScore;

	EXPECT_EQ(0, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 3 letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 3Letters)
{
	Score player_score;

	player_score.m_word = "her";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(1, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 4 letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 4Letters)
{
	Score player_score;

	player_score.m_word = "poop";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(1, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 5 letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 5Letters)
{
	Score player_score;

	player_score.m_word = "whoop";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(2, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 6 letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 6Letters)
{
	Score player_score;

	player_score.m_word = "whoops";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(3, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 7 letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 7Letters)
{
	Score player_score;

	player_score.m_word = "whoopsy";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(4, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 8 or more letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 8Letters)
{
	Score player_score;

	player_score.m_word = "cocacola";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(11, player_score.m_playerScore);
}

/// <summary>
/// Tests the score if word is 17 letters long
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 17Letters)
{
	Score player_score;

	player_score.m_word = "cocacolacocacolac";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(11, player_score.m_playerScore);
}

/// <summary>
/// checking if score is adding correctly from different length words
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 6LettersPlus3Letters)
{
	Score player_score;

	player_score.m_word = "cocaco";

	player_score.m_calculateScore(player_score.m_word);

	player_score.m_word = "coc";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(4, player_score.m_playerScore);
}

/// <summary>
/// checking if score is adding correctly from different length words
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(Score, 2LettersPlus9Letters)
{
	Score player_score;

	player_score.m_word = "co";

	player_score.m_calculateScore(player_score.m_word);

	player_score.m_word = "cocacolac";

	player_score.m_calculateScore(player_score.m_word);

	EXPECT_EQ(11, player_score.m_playerScore);
}

TEST(dontGivePoints, 1Word) {
	StoreUsedWords t_wordStorage;

	std::string tempWord = "killer";

	bool checkIfRepeat;

	checkIfRepeat = t_wordStorage.checkIfRepeatWord(tempWord);

	EXPECT_FALSE(checkIfRepeat);
}

TEST(dontGivePoints, 2Words) {
	StoreUsedWords t_wordStorage;

	std::string tempWord = "killer";

	std::string tempWord2 = "killerWhale";

	bool checkIfRepeat;

	if (t_wordStorage.checkIfRepeatWord(tempWord) == true)
	{
		checkIfRepeat = true;

		if (t_wordStorage.checkIfRepeatWord(tempWord2) == true)
		{
			checkIfRepeat = true;
		}
	}

	checkIfRepeat = false;

	EXPECT_FALSE(checkIfRepeat);
}
