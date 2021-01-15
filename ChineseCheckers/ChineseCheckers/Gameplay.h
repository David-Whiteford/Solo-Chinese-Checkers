#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include "Player.h"
#include "Board.h"
#include "Button.h"
#include <array>
#include "Globals.h"
#include "AI.h"

enum class Turn
{
	Player,
	AI
};

class GamePlay
{
public:
	GamePlay();
	~GamePlay();
	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font, sf::RenderWindow& t_window);
	void initialise();

	//Turn
	static Turn m_currentTurn;

private:
	//Font
	sf::Font m_font;
	Player m_player;
	AI m_AI;

	static const int m_amountOfPlayers = 2;
	std::array<Button, m_amountOfPlayers> m_turnIndicator;
	void currentTurn();
	void m_nextPlayersTurn();

	//Board
	Board* m_board;


	//timer
	float m_timer = 0;
	float m_minWaitForTime = 250;

	void checkAIWin();
	void checkPlayerWin();

};