#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::movePiece(sf::RenderWindow& t_window)
{
	sf::Vector2f offset = sf::Vector2f(10, 10);
	int x = sf::Mouse::getPosition(t_window).x;
	int y = sf::Mouse::getPosition(t_window).y;
	sf::Vector2f newMousePos;
	newMousePos.x = x;
	newMousePos.y = y;
	m_pegHolesVec = m_board->getBoardHoles();
	m_raysVec = m_board->getRays();
	
	for (int i = 0; i < m_playerPieces.size(); i++)
	{
		sf::Vector2f mousePos = sf::Vector2f(newMousePos.x, newMousePos.y);
		sf::Vector2f circlePos = m_playerPieces[i]->getPosition();
		if(m_colisions.pointCircleCol(mousePos, circlePos, m_pegRadius)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pieceHeld == false)
		{
			m_pieceIndex = i;
			m_pieceHeld = true;	
			m_moseButtonReleased = false;
			m_currentPress++;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	{
		m_pieceHeld = false;
		if (m_currentPress == 1)
		{
			m_moseButtonReleased = true;
			m_currentPress = 0;
		}
	}
	if (m_doOnce == 0 && m_pieceHeld)
	{
		for (int j = 0; j < m_raysVec.size(); j++)
		{
			sf::Vector2f point = m_raysVec[j]->getRayStartPos();
			sf::Vector2f circlePos = m_playerPieces[m_pieceIndex]->getPosition();
			if (m_colisions.pointCircleCol(point, circlePos,m_pegRadius))
			{
				m_endRaysVec.push_back(m_raysVec[j]);
			}		
		}
		m_doOnce++;
	}
	if (m_pieceHeld)
	{
		
		m_playerPieces[m_pieceIndex]->setPosition(newMousePos- offset);
	}
	if(m_moseButtonReleased)
	{
		for (int i = 0; i < m_endRaysVec.size(); i++)
		{
			sf::Vector2f point = m_endRaysVec[i]->getEndPoint();
			sf::Vector2f circlePos = m_playerPieces[m_pieceIndex]->getPosition();
			if(m_colisions.pointCircleCol(point, circlePos,m_pegRadius) == true)
			{
				m_playerPieces[m_pieceIndex]->setPosition(m_endRaysVec[i]->getEndPoint() - offset);
			}
			else {
				m_playerPieces[m_pieceIndex]->setPosition(m_initialPos[m_pieceIndex]);
			}
		
		}
		m_endRaysVec.clear();
		m_doOnce = 0;
	}
	PegHoles* peg = m_board->getPegHole(m_raysVec[6]);
	//std::cout << "PEg PosX: " << peg->getPosition().x << "PEg PosY: " << peg->getPosition().y << std::endl;
}

void Player::setUpPieces(sf::RenderWindow& t_window,Board *t_board)
{
	m_board = t_board;
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
