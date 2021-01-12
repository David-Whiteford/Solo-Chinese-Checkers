#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieces.h"
#include "Board.h"


//Move Struct
struct AiMove {
	AiMove() {};
	AiMove(int Score) : score(Score) {}

	Pieces *aiPiece;
	PegHoles* destinationPegHole;
	int score;
};

class AI
{
public:
	AI();
	~AI();
	void setUpPieces(sf::RenderWindow& t_window, Board* t_board);
	void draw();

	//Movement
	void takeTurn();
	//AiMove bestMove(int t_player);

private:
	//All Pieces and Pegholes
	std::vector<Pieces*> m_AIPieces;
	std::vector<PegHoles*> m_pegHolesVec;
	const int MAX_PIECES = 10;

	const int m_AI_PLAYER = 1;
	const int m_HUMAN_PLAYER = 2;


};