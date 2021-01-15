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
	PegHoles *destinationPegHole;
	int score;
};

class AI
{
public:
	AI();
	~AI();
	void setUpPieces(sf::RenderWindow& t_window, Board* t_board);
	void draw(sf::RenderWindow& t_window);
	void update(Board * t_board);

	//Movement
	void takeTurn();
	AiMove bestMove(int t_player, Board t_board, int t_depth);
	std::vector<Pieces* > getAIPieces();
private:
	//collision object
	Collisions m_colisions;
	//All Pieces and Pegholes
	std::vector<Pieces*> m_AIPieces;
	std::vector<PegHoles*> m_pegHolesVec;
	std::vector<Raycast*> m_endrays;
	std::vector<Raycast*> m_raysVec;
	std::vector<PegHoles*> m_startingHoles;




	//The size of the piece radius
	int m_pegRadius = 10;
	//const int MAX_PIECES = 10;
	//const int m_places = 1;
	const int m_places = 10;
	//const int m_places = 1;
	const int m_AI_PLAYER = 1;
	const int m_HUMAN_PLAYER = 2;
	Board* m_board;
	int m_doOnce = 0;
	void performMove(AiMove t_move, Board t_board);
	void undoMove(AiMove t_move);
	sf::Vector2f m_offset = sf::Vector2f(10, 10);
	int MAX_DEPTH = 0;

	int m_scoring(AiMove* t_move);

	std::vector<PegHoles*> m_goalPegHoles;


};