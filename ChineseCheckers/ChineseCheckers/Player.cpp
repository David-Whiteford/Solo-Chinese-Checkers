#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::movePiece(sf::RenderWindow& t_window)
{
	grabPiece(t_window);
	placePiece();
	for (int i = 0; i < m_pegHolesVec.size(); i++)
	{
		//std::cout << "Get the peg tag 13: " << m_pegHolesVec[13]->getPegOccupied() << std::endl;

		std::cout << "Get the peg tag 28: " << m_pegHolesVec[28]->getPegOccupied() << std::endl;

		/*std::cout << "Get the peg tag 49: " << m_pegHolesVec[49]->getPegOccupied() << std::endl;*/

	}

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
				m_resetPos.push_back(t_board->getBoardHoles()[i]->getPosition());
			}
		}
	}
	for (int i = 0; i < m_playerPieces.size(); i++) {
		m_allPieces.push_back(m_playerPieces[i]);
	}
	m_board->setAllPieces(m_playerPieces);
}

void Player::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_playerPieces.size(); ++i)
	{
		m_playerPieces[i]->draw();
	}
	for (int i = 0; i < m_endRaysVec.size(); i++)
	{
		t_window.draw(m_endRaysVec[i]->drawRay());
	}

	
}
void Player::grabPiece(sf::RenderWindow& t_window)
{
	int x = sf::Mouse::getPosition(t_window).x;
	int y = sf::Mouse::getPosition(t_window).y;
	m_newMousePos.x = x;
	m_newMousePos.y = y;
	m_pegHolesVec = m_board->getBoardHoles();
	m_raysVec = m_board->getRays();

	for (int i = 0; i < m_playerPieces.size(); i++)
	{
		sf::Vector2f mousePos = sf::Vector2f(m_newMousePos.x, m_newMousePos.y);
		sf::Vector2f circlePos = m_playerPieces[i]->getPosition();
		if (m_colisions.pointCircleCol(mousePos, circlePos, m_pegRadius)
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
		for (int i = 0; i < m_raysVec.size(); i++)
		{
			if (m_colisions.pointCircleCol(m_raysVec[i]->getRayStartPos(),
				m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius))
			{
				m_endRaysVec.push_back(m_raysVec[i]);
			}
		}
		m_doOnce++;
	}
}
void Player::checkEndRaysCol(std::vector<Raycast*> t_pegNeighbours)
{
	for (int i = 0; i < t_pegNeighbours.size(); i++)
	{
		//std::cout << "I " << i << std::endl;
		if (m_colisions.pointCircleCol(t_pegNeighbours[i]->getEndPoint(),
			m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius))
		{
			m_newPiecePos = t_pegNeighbours[i]->getEndPoint() - m_offset;
			return;
		}
		else if (m_colisions.pointCircleCol(t_pegNeighbours[i]->getEndPoint(),
			m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius) == false)
		{
			m_newPiecePos = m_resetPos[m_pieceIndex];
		}
	}
}
void Player::placePiece()
{
	if (m_pieceHeld)
	{
		m_playerPieces[m_pieceIndex]->setPosition(m_newMousePos - m_offset);
		pegOccupiedCheck();
		//m_endRaysVec = m_board->pegOccupiedCheck(m_playerPieces[m_pieceIndex],m_playerPieces);
		checkEndRaysCol(m_endRaysVec);

		for (int i = 0; i < m_pegHolesVec.size(); i++)
		{
			sf::Vector2f point = m_playerPieces[m_pieceIndex]->getPosition();
			sf::Vector2f circlePos = m_pegHolesVec[i]->getPosition();
			if (m_colisions.pointCircleCol(point, circlePos, m_pegRadius))
			{
				m_pegIndex = i;
			}
			//std::cout << "IS Occupied: " << m_pegHolesVec[i]->getPegOccupied() << std::endl;
		}
	}
	if (m_moseButtonReleased)
	{
		m_resetPos[m_pieceIndex] = m_newPiecePos;
		m_playerPieces[m_pieceIndex]->setPosition(m_newPiecePos);
		m_pieceHeld = false;
		m_endRaysVec.clear();
		m_doOnce = 0;
		m_jumpAvailable = 0;
	}
}
void Player::pegOccupiedCheck()
{
	m_allPieces = m_board->getAllPieces();
	for (int i = 0; i < m_playerPieces.size(); i++)
	{
		for (int j = 0; j < m_allPieces.size(); j++)
		{
			if (i == j) {}
			else
			{

				if (m_colisions.pointCircleCol(m_playerPieces[i]->getPosition() + m_offset,
					m_allPieces[j]->getPosition(), m_pegRadius))
				{
					if (m_jumpAvailable == 0)
					{
						std::vector<Raycast*> pegNeighbours = m_board->setNeighboursRays(m_playerPieces[m_pieceIndex]);
						m_endRaysVec.clear();
						m_endRaysVec = pegNeighbours;
						m_jumpAvailable++;
					}
				}
			}

		}
	}

}
