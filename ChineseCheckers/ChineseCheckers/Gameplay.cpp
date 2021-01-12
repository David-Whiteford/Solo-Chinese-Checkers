#include "Gameplay.h"

Turn m_currentTurn{ Turn::Player};

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{
	for (Button indicatorButton : m_turnIndicator)
	{
		indicatorButton.update(t_deltaTime);
	}
	currentTurn();

	m_player.movePiece(t_window);

}

void GamePlay::render(sf::RenderWindow& t_window)
{
	m_player.draw();

	m_AI.draw();

	for (Button indicatorButton : m_turnIndicator)
	{
		indicatorButton.render(t_window);
	}

}

void GamePlay::setup(sf::Font& t_font, sf::RenderWindow& t_window, Board* t_board)
{
	m_player.setUpPieces(t_window,t_board);
	m_AI.setUpPieces(t_window, t_board);

	for (Button indicatorButton : m_turnIndicator)
	{
		indicatorButton.setup(t_font);
	}

	m_turnIndicator.at(0).setInfo("Your Turn", 100, 30, sf::Vector2f(420, 20));
	m_turnIndicator.at(1).setInfo("AI Turn", 100, 30, sf::Vector2f(540, 20));

}

void GamePlay::initialise()
{
}

void GamePlay::currentTurn()
{
	switch (m_currentTurn)
	{
	case Turn::Player:
		m_turnIndicator.at(0).setSelected(true);
		m_turnIndicator.at(1).setSelected(false);
		break;
	case Turn::AI:
		m_turnIndicator.at(0).setSelected(false);
		m_turnIndicator.at(1).setSelected(true);
		break;
	default:
		break;
	}
}

void GamePlay::m_nextPlayersTurn()
{
	if (static_cast<int>(m_currentTurn) < m_amountOfPlayers)
	{
		m_currentTurn = static_cast<Turn>(static_cast<int>(m_currentTurn) + 1);
	}
	else
	{
		m_currentTurn = static_cast<Turn>(0);
	}
}
