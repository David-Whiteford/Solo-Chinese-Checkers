#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::movePiece(int t_newX, int t_newY, sf::RenderWindow& t_window)
{
	int x = sf::Mouse::getPosition(t_window).x;
	int y = sf::Mouse::getPosition(t_window).y;
	sf::Vector2f newMousePos;
	newMousePos.x = x;
	newMousePos.y = y;
	
	std::cout << "MosueX:" << newMousePos.x << "MosueY:" << newMousePos.y << std::endl;

	for (int i = 0; i < m_playerPieces.size(); i++)
	{
		if (newMousePos.x > m_playerPieces[i]->getPosition().x - m_pegRadius 
			&& newMousePos.x < m_playerPieces[i]->getPosition().x + m_pegRadius
			&& newMousePos.y > m_playerPieces[i]->getPosition().y - m_pegRadius 
			&& newMousePos.y < m_playerPieces[i]->getPosition().y + m_pegRadius)
		{
			m_pieceIndex = i;
			std::cout << "m_pieceIndex:" << m_pieceIndex << std::endl;
		}
		
	}
}

void Player::setUpPieces(sf::RenderWindow& t_window,Board *t_board)
{
	m_pegHolesVec = t_board->getBoardHoles();
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
