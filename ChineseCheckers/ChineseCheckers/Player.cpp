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
	testCircle.setPosition(sf::Vector2f(-111, -111));
	testCircle.setFillColor(sf::Color::Cyan);
	testCircle.setRadius(2);
	testCircle.setOrigin(1, 1);
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

	std::cout << m_endRaysVec.size() << std::endl;

	t_window.draw(testCircle);
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

void Player::placePiece()
{
	if (m_pieceHeld)
	{
		m_playerPieces[m_pieceIndex]->setPosition(m_newMousePos - m_offset);
		sf::Vector2f originalRayEndPos;
		for (int i = 0; i < m_endRaysVec.size(); i++)
		{
			//std::cout << "I " << i << std::endl;
			if (m_colisions.pointCircleCol(m_endRaysVec[i]->getEndPoint(), m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius))
			{
		
				m_newPiecePos = m_endRaysVec[i]->getEndPoint() - m_offset;
				m_piecePlaced = true;
				m_positionFound = true;
				return;
			}
			else if (m_colisions.pointCircleCol(m_endRaysVec[i]->getEndPoint(),
				m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius) == false)
			{
				m_newPiecePos = m_resetPos[m_pieceIndex];
			}
			else if (m_pegHolesVec[m_pegIndex]->getPegOccupied() == true)
			{
				m_endRaysVec[i]->setRayValues(m_endRaysVec[i]->getRayStartPos(), m_endRaysVec[i]->getDirection(),
					m_endRaysVec[i]->getRayLength() * 2);
			}
		}

		testCircle.setPosition(m_newPiecePos);
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
		if (m_pegHolesVec[m_pegIndex]->getPegOccupied() == false)
		{
			m_resetPos[m_pieceIndex] = m_newPiecePos;
			m_playerPieces[m_pieceIndex]->setPosition(m_newPiecePos);
			//m_pegHolesVec[m_pegIndex]->setTeamTag("Blue");
			//m_pegHolesVec[m_pegIndex]->setPegOccupied(true);
		}
		m_pieceHeld = false;
		m_endRaysVec.clear();
		m_doOnce = 0;
	}
}
