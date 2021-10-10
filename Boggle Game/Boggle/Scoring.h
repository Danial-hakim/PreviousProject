//Includes
#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

/// <summary>
/// This class handles everything to do with the Score
/// </summary>
class Score
{
public:
	//Public Member Variables
	int m_playerScore; //Player Score
	std::string m_word; //Word inputted by the player

	int m_highestPlayerScore;

	//Public Member Methods

	/// <summary>
	/// Handles player input and output aswell as running m_calculateScore();
	/// </summary>
	void m_processScore(std::string t_word);

	/// <summary>
	/// calculates how much score player gains from word entered
	/// </summary>
	/// <returns>m_score</returns>
	void m_calculateScore(std::string t_word);


	void m_resetScore();
	//Constructor and Destructor
	Score() {
		m_playerScore = 0;
		m_highestPlayerScore = 0;
		m_word = "";
	};

private:

};



