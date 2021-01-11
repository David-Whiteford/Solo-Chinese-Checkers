#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::movePiece(sf::RenderWindow& t_window)
{
	
	int x = sf::Mouse::getPosition(t_window).x;
	int y = sf::Mouse::getPosition(t_window).y;
	sf::Vector2f newMousePos;
	newMousePos.x = x;
	newMousePos.y = y;
	
	std::cout << "MosueX:" << newMousePos.x << "MosueY:" << newMousePos.y << std::endl;

	for (int i = 0; i < m_playerPieces.size(); i++)
	{
		if (newMousePos.x < m_playerPieces[i]->getPosition().x + m_pegRadius *2
			&& newMousePos.x  > m_playerPieces[i]->getPosition().x 
			&& newMousePos.y < m_playerPieces[i]->getPosition().y + m_pegRadius*2
			&& newMousePos.y > m_playerPieces[i]->getPosition().y 
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pieceHeld == false)
		{
			m_pieceIndex = i;
			m_pieceHeld = true;	
			m_moseButtonReleased = false;
			m_currentPress++;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
		{
			m_pieceHeld = false;
			if (m_currentPress == 1)
			{
				m_moseButtonReleased = true;
				m_currentPress = 0;
			}
		}
	}
	if (m_pieceHeld)
	{
		
		m_playerPieces[m_pieceIndex]->setPosition(newMousePos);
		for (int i = 0; i < m_pegHolesVec.size(); i++)
		{
			if (newMousePos.x < m_pegHolesVec[i]->getPosition().x + m_pegRadius * 2
				&& newMousePos.x  > m_pegHolesVec[i]->getPosition().x 
				&& newMousePos.y < m_pegHolesVec[i]->getPosition().y + m_pegRadius * 2
				&& newMousePos.y > m_pegHolesVec[i]->getPosition().y)
			{
				m_newPiecePos = m_pegHolesVec[i]->getPosition();
				m_pegIndex = i;
				m_placePiece = true;
			}
		}
	}
	
	else if(m_moseButtonReleased)
	{
		if (m_pegHolesVec[m_pegIndex]->getPegOccupied() == false )
		{	
			
				m_playerPieces[m_pieceIndex]->setPosition(m_newPiecePos);
				m_pegHolesVec[m_pegIndex]->setTeamTag("Blue");
				m_pegHolesVec[m_pegIndex]->setPegOccupied(true);
			
		}
		for (int i = 0; i < m_playerPieces.size(); i++)
		{
			if (m_playerPieces[m_pieceIndex]->getPosition().x < m_playerPieces[i]->getPosition().x + m_pegRadius * 2
				&& m_playerPieces[m_pieceIndex]->getPosition().x  > m_playerPieces[i]->getPosition().x
				&& m_playerPieces[m_pieceIndex]->getPosition().y < m_playerPieces[i]->getPosition().y + m_pegRadius * 2
				&& m_playerPieces[m_pieceIndex]->getPosition().y > m_playerPieces[i]->getPosition().y)
			{
				m_playerPieces[m_pieceIndex]->setPosition(m_initialPos[m_pieceIndex]);
			}
		}
	}


}

void Player::setUpPieces(sf::RenderWindow& t_window,Board *t_board)
{
	if (m_sideTop == true)
	{
		for (int i = 0; i < m_maxPlaces;i++)
		{
			if (t_board->getBoardHoles()[i]->getColor() == sf::Color::Green) {}
			else
			{
				m_playerPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i]->getPosition(), sf::Color::Blue));
				m_initialPos.push_back(t_board->getBoardHoles()[i]->getPosition());
			}
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
