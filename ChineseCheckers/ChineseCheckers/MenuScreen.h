#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Button.h"
#include <array>


enum class menuButtons {
	playGame,
	howToPlay,
	options,
	exit
};

class Menu
{
public:
	Menu();
	~Menu();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void loadTextures();

private:
	//Button Array
	static const int m_ammountOfButtons = 4;
	std::array<Button, m_ammountOfButtons> buttons;

	void m_playButtonSetUp();
	void m_howToPlaySetUp();
	void m_optionsSetUp();
	void m_exitSetUp();
	
	float buttonX = 420;
	float buttonY = 50;
	float offset = 20;

	//Current Select
	menuButtons m_currentMode { menuButtons::playGame };
	void m_currentButtonSelect();

	//Input
	void input(sf::Time t_deltaTime);
	float m_timer;
	float m_minWaitForTime = 250;


	//Display
	void display();
	//Text
	sf::Font m_font;
	sf::Text m_startGameText;
	sf::Text m_howToPlayText;
	sf::Text m_exitText;

	std::string startString = "Welcome to Chinese Checkers! \n Press Enter to Start a new Game";
	std::string howToPlayString = "The aim of the game is to \n be the first to player to move \nall ten pegs across the board \n and into the triangle opposite. \nThe first player to occupy all \n10 destination holes is the winner.";


	//Difficulty
	const static int m_amountOfDifficultyOptions = 3;
	std::array<Button, m_amountOfDifficultyOptions> m_difficultyButtons;

	void m_currentDifficultySelected();

	void m_easyButtonSetUp();
	void m_normalButtonSetUp();
	void m_hardButtonSetUp();
};