#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collisions.h"
#include "Pieces.h"
#include "Board.h"
class Player
{
public:
	Player();
	~Player();
	void movePiece(sf::RenderWindow& t_window);
	void setUpPieces(sf::RenderWindow& t_window, Board* t_board);
	void draw(sf::RenderWindow& t_window);

private:
	Collisions m_colisions;
	Board* m_board;
	std::vector<Pieces*> m_playerPieces;
	int m_index = 0;
	bool m_sideTop = true;
	int m_doOnce = 0;
	int m_maxPlaces = 16;
	std::vector<Raycast*> m_raysVec;
	std::vector<Raycast*> m_endRaysVec;
	std::vector<PegHoles*> m_neighboursVec;
	std::vector<PegHoles*> m_pegHolesVec;
	sf::CircleShape testCircle;
	int m_pegRadius = 10;
	int m_pieceIndex = 11;
	int m_pegIndex = 0;
	bool piecePlaced = false;
	bool m_pieceHeld = false;
	bool m_moseButtonReleased = false;
	bool m_piecePlaced = false;
	bool m_positionFound = false;
	int m_currentPress = 0;
	std::vector<sf::Vector2f> m_resetPos;
	sf::Vector2f m_mousePos = sf::Vector2f(0,0);
	sf::Vector2f m_newPiecePos = sf::Vector2f(0, 0);
	bool m_newPosFound = true;
	sf::Vector2f m_offset = sf::Vector2f(10, 10);
};

