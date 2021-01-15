#include "Gameplay.h"


Turn GamePlay::m_currentTurn{ Turn::AI };

GamePlay::GamePlay()
{
	m_board = new Board();
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{
	m_board->setPegHoleOccupied(m_player.getPieces(), m_AI.getAIPieces() );

	if (m_currentTurn == Turn::AI)
	{
		//Update the AI
		m_AI.update(m_board);
		//m_AI.takeTurn();
	}
	else
	{
		//Players Turn here
		m_player.movePiece(t_window);
	}

	//m_board->setPegHoleOccupied(m_playerPieces);

	if (m_timer < m_minWaitForTime)
	{
		m_timer += t_deltaTime.asMilliseconds();
	}

	if (m_timer >= m_minWaitForTime)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{


			if (m_currentTurn == Turn::Player)
			{
				m_currentTurn = Turn::AI;
			}
			m_timer = 0;
		}
	}

	currentTurn();

	for (Button indicatorButton : m_turnIndicator)
	{
		indicatorButton.update(t_deltaTime);
	}




}

void GamePlay::render(sf::RenderWindow& t_window)
{
	m_board->Draw(t_window);

	m_player.draw(t_window);

	m_AI.draw(t_window);


	for (Button indicatorButton : m_turnIndicator)
	{
		indicatorButton.render(t_window);
	}

}

void GamePlay::setup(sf::Font& t_font, sf::RenderWindow& t_window)
{
	m_board->setMap(t_window);
	m_board->setUpRays();

	m_player.setUpPieces(t_window,m_board);
	m_AI.setUpPieces(t_window, m_board);

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
