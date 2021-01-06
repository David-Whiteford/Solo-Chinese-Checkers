#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::movePiece(int t_newX, int t_newY)
{
}

void Player::setUpPieces(sf::RenderWindow& t_window,Board *t_board)
{
	if (m_sideTop == true)
	{
		for (int i = 0; i < m_maxPlayerPieces;)
		{
			m_playerPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i]->getPosition(), sf::Color::Blue));
			i++;
		}
	}
}

void Player::draw()
{
	for (int i = 0; i < m_playerPieces.size(); ++i)
	{
		m_playerPieces[i]->draw();
	}
}
