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
	m_pegHolesVec = m_board->getBoardHoles();
	m_raysVec = m_board->getRays();

	for (int i = 0; i < m_playerPieces.size(); i++)
	{
		sf::Vector2f mousePos = sf::Vector2f(newMousePos.x, newMousePos.y);
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
		//for (int j = 0; j < m_pegHolesVec.size(); j++)
		//{
		//	sf::Vector2f point = m_playerPieces[m_pieceIndex]->getPosition() + offset;
		//	sf::Vector2f circlePos = m_pegHolesVec[j]->getPosition();
		//	if (m_colisions.pointCircleCol(point, circlePos, m_pegRadius))
		//	{
		//		m_neighboursVec = m_pegHolesVec[j]->getNeighbours();
		//		
		//	}
		//	for (int i = 0; i < m_neighboursVec.size(); i++)
		//	{
		//		m_neighboursVec[i]->setColor(sf::Color::Cyan);
		//	}
		//}
		for (int i = 0; i < m_raysVec.size(); i++)
		{
			if (m_colisions.pointCircleCol(m_raysVec[i]->getRayStartPos(),
				m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius))
			{
				m_endRaysVec.push_back(m_raysVec[i]);
			}
		}
		std::cout << m_raysVec.size() << std::endl;
		m_doOnce++;
	}
	if (m_pieceHeld)
	{
		m_playerPieces[m_pieceIndex]->setPosition(newMousePos - m_offset);
		//for (int i = 0; i < m_neighboursVec.size(); i++)
		//{
		//	sf::Vector2f point = m_playerPieces[m_pieceIndex]->getPosition() + offset;
		//	sf::Vector2f circlePos = m_neighboursVec[i]->getPosition();
		//	if (m_colisions.pointCircleCol(point, circlePos, m_pegRadius) == true)
		//	{
		//		m_newPiecePos = m_neighboursVec[i]->getPosition();
		//		m_piecePlaced = true;
		//		m_positionFound = true;
		//	}
		//	else
		//	{
		//		m_newPiecePos = m_resetPos[m_pieceIndex];
		//	}
		//}

		for (int i = 0; i < m_endRaysVec.size(); i++)
		{
			//std::cout << "I " << i << std::endl;
			if (m_colisions.pointCircleCol(m_endRaysVec[i]->getEndPoint(), m_playerPieces[m_pieceIndex]->getPosition(), m_pegRadius))
			{
				//m_playerPieces[m_pieceIndex]->setPosition(m_endRaysVec[i]->getEndPoint() - offset);
				m_newPiecePos = m_endRaysVec[i]->getEndPoint() - m_offset;
				m_piecePlaced = true;
				m_positionFound = true;

			}
			else
			{
				m_newPiecePos = m_resetPos[m_pieceIndex];
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
		}
	}
	if (m_moseButtonReleased)
	{
		m_pieceHeld = false;
		if (m_pegHolesVec[m_pegIndex]->getPegOccupied() == false)
		{
			m_resetPos[m_pieceIndex] = m_newPiecePos;
			m_playerPieces[m_pieceIndex]->setPosition(m_newPiecePos);
			m_pegHolesVec[m_pegIndex]->setTeamTag("Blue");
			m_pegHolesVec[m_pegIndex]->setPegOccupied(true);
		}
		m_endRaysVec.clear();
		m_doOnce = 0;
	}

	//PegHoles* peg = m_board->getPegHole(m_raysVec[6]);
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
	t_window.draw(testCircle);
}
