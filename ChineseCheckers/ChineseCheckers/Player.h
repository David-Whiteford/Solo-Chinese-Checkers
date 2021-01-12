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
	void draw();

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
	std::vector<PegHoles*> m_pegHolesVec;
	int m_pegRadius = 10;
	int m_pieceIndex = 11;
	int m_pegIndex = 0;
	bool m_pieceHeld = false;
	bool m_moseButtonReleased = false;
	bool m_placePiece = false;
	int m_currentPress = 0;
	std::vector<sf::Vector2f> m_initialPos;
	sf::Vector2f m_mousePos = sf::Vector2f(0,0);
	sf::Vector2f m_newPiecePos = sf::Vector2f(0, 0);
	bool m_newPosFound = true;

};

