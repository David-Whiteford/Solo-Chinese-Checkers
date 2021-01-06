#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieces.h"
#include "Board.h"
class Player
{
public:
	Player();
	~Player();
	void movePiece(int t_newX,int t_newY, sf::RenderWindow& t_window);
	void setUpPieces(sf::RenderWindow& t_window, Board* t_board);
	void draw();

private:
	std::vector<Pieces*> m_playerPieces;
	int m_index = 0;
	bool m_sideTop = true;
	Board m_board;
	int m_maxPlayerPieces = 10;
	std::vector<PegHoles*> m_pegHolesVec;
	int m_pegRadius = 10;
	int m_pieceIndex = 0;
	bool m_mousePressed = false;
	bool m_mouseReleased = false;
	sf::Vector2f m_initialPos=sf::Vector2f(0, 0);
	sf::Vector2f m_mousePos = sf::Vector2f(0,0);

};

