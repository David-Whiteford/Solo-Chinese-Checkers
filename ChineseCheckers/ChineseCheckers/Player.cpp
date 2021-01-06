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
			&& newMousePos.y < m_playerPieces[i]->getPosition().y + m_pegRadius
			&& m_pieceHeld == false)
		{
			m_pieceIndex = i;
			//std::cout << "m_pieceIndex:" << m_pieceIndex << std::endl;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_playerPieces[m_pieceIndex]->setPosition(newMousePos);
		for (int i = 0; i < m_pegHolesVec.size(); i++)
		{
			if (newMousePos.x + m_pegRadius > m_pegHolesVec[i]->getPosition().x - m_pegRadius
				&& newMousePos.x - m_pegRadius < m_pegHolesVec[i]->getPosition().x + m_pegRadius
				&& newMousePos.y + m_pegRadius > m_pegHolesVec[i]->getPosition().y - m_pegRadius
				&& newMousePos.y - m_pegRadius < m_pegHolesVec[i]->getPosition().y + m_pegRadius)
			{
				m_newPiecePos = m_pegHolesVec[i]->getPosition();
				m_newPosFound = true;

			}
		}
		m_pieceHeld = true;
	}

	std::cout << "m_pieceHeld: " << m_pieceHeld << std::endl;
}

void Player::setUpPieces(sf::RenderWindow& t_window,Board *t_board)
{
	m_pegHolesVec = t_board->getBoardHoles();
	if (m_sideTop == true)
	{
		for (int i = 0; i < m_maxPlayerPieces;)
		{
			m_playerPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i]->getPosition(), sf::Color::Blue));
			m_initialPos.push_back(t_board->getBoardHoles()[i]->getPosition());
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
