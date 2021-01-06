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
	void movePiece(int t_newX,int t_newY);
	void setUpPieces(sf::RenderWindow& t_window, Board* t_board);
	void draw();

private:
	std::vector<Pieces*> m_playerPieces;
	int m_index = 0;
	bool m_sideTop = true;
	Board m_board;
	int m_maxPlayerPieces = 10;

};

