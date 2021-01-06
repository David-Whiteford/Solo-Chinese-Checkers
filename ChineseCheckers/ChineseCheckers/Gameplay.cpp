#include "Gameplay.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{

}

void GamePlay::render(sf::RenderWindow& t_window)
{
	m_player.draw();
}

void GamePlay::setup(sf::Font& t_font, sf::RenderWindow& t_window, Board* t_board)
{
	m_player.setUpPieces(t_window,t_board);
}

void GamePlay::initialise()
{
}
