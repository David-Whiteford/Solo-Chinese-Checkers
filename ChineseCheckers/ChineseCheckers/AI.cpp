#include "AI.h"
#include "Gameplay.h"

AI::AI()
{
	srand(time(NULL));
}

AI::~AI()
{
}

void AI::setUpPieces(sf::RenderWindow& t_window, Board* t_board)
{
	m_pegHolesVec = t_board->getBoardHoles();
	for (int i = t_board->getBoardHoles().size() - 1; i > t_board->getBoardHoles().size() - m_places - 1;--i)
	{
		if (t_board->getBoardHoles()[i]->getColor() == sf::Color::Green) {}
		else
		{
			m_AIPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i -11 ]->getPosition(), sf::Color::Red));
		}
	}
}

void AI::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_AIPieces.size(); ++i)
	{
		m_AIPieces[i]->draw();
	}
	for (int i = 0; i < m_endrays.size(); i++)
	{
		t_window.draw(m_endrays[i]->drawRay());
	}
	
}

void AI::update(Board* t_board)
{

	m_board = t_board;
	
	

	takeTurn();
	std::vector<PegHoles*> adjacentPegHoles = m_board->getPieceNeigthbours(m_AIPieces.at(0));
	/*for (PegHoles* adjacentPegHole : adjacentPegHoles)
	{
		adjacentPegHole->changeColor(sf::Color::Magenta);
	}*/
	




}

void AI::takeTurn()
{
	AiMove move = bestMove(1, *m_board, 0);

	move.aiPiece->setPosition(move.destinationPegHole->getPosition());

	GamePlay::m_currentTurn = Turn::Player;
}


AiMove AI::bestMove(int t_player, Board t_board, int t_depth = 0)
{
	//std::cout << t_depth << std::endl;
	std::vector<AiMove> moves;
	m_raysVec = m_board->getRays();
	//Go through all of the pieces
	for (Pieces* piece : m_AIPieces)
	{
		std::cout << "piece vec Size: " << m_AIPieces.size() << std::endl;
		sf::Vector2f originalPos = piece->getPosition();
		//if (m_doOnce == 0)
		//{
		//	for (int i = 0; i < m_raysVec.size(); i++)
		//	{
		//		if (m_colisions.pointCircleCol(m_raysVec[i]->getRayStartPos(),
		//			piece->getPosition() + m_offset, m_pegRadius))
		//		{
		//			m_endrays.push_back(m_raysVec[i]);
		//			piece->setNeighboursRays(m_raysVec[i]);
		//		}
		//	}
		//	m_doOnce++;
		//	//std::cout << "Ray Size: " << m_endrays.size() << std::endl;
		//}
		




		//Get array of surrounding peg holes
		std::vector<PegHoles*> adjacentPegHoles = t_board.getPieceNeigthbours(piece);



		//Go through each adjacent Hole
		for (PegHoles* pegHole : adjacentPegHoles)
		{
			//Create the move
			AiMove availibleMove;

			//Check Ocupied
			if (pegHole->getPegOccupied())
			{
				//Difference between two vectors
				//sf::Vector2f vectorToPeghole()

				/*
				PegHoles* pegHoleOver = pegHole.getPegHoleOver() // <----------------- NEED A FUNCTION RETURNING POINTER TO PEG HOLE THAT IS OVER THE CURRENT ONE

				if(pegHoleOver.isOcupied)
				{
					//do nothing
				}
				else
				{
					if (t_player == m_AI_PLAYER) {
                    move.score = getBestMove(m_HUMAN_PLAYER).score;
					} 
					else {
                    move.score = getBestMove(m_AI_PLAYER).score;
					}

					AiMove availibleMove;
					move.aiPiece = piece;
					move.destinationPegHole = pegHoleOver;


					moves.push_back(availibleMove)
				}
				*/
			}
			else
			{
				std::cout << "Called" << std::endl;
				//Perform Move
				piece->setPosition(pegHole->getPosition());
				//m_doOnce = 0;

				availibleMove.aiPiece = piece;
				availibleMove.destinationPegHole = pegHole;
				availibleMove.score = rand() % 300;
			}			

			//Reccusively min max
			if (t_depth < MAX_DEPTH)
			{
				if (t_player == m_AI_PLAYER) {

					availibleMove.score = bestMove(m_HUMAN_PLAYER, t_board, t_depth + 1).score;
				}
				else {
					availibleMove.score = bestMove(m_AI_PLAYER, t_board, t_depth + 1).score;
				}
			}

			//Undo move
			piece->setPosition(originalPos);

			moves.push_back(availibleMove);
		}
	}

	// Pick the best move for the current player
	int bestMove = 0;
	if (t_player == m_AI_PLAYER) {
		int bestScore = -1000000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else {
		int bestScore = 1000000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	
	
	return moves.at(bestMove);
}

void AI::performMove(AiMove t_move, Board t_board)
{
	t_move.aiPiece->setPosition(t_move.destinationPegHole->getPosition());
}

void AI::undoMove(AiMove t_move)
{
	t_move.aiPiece->setPosition(t_move.destinationPegHole->getPosition());
}


