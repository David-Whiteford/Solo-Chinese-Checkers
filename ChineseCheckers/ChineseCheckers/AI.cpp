#include "AI.h"

AI::AI()
{
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
			//m_AIPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[t_board->getBoardHoles().size()]->getPosition(), sf::Color::Red));
			m_AIPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i]->getPosition(), sf::Color::Red));
			//m_initialPos.push_back(t_board->getBoardHoles()[i]->getPosition());
			
		}
	}
}

void AI::draw()
{
	for (int i = 0; i < m_AIPieces.size(); ++i)
	{
		m_AIPieces[i]->draw();
	}
}

void AI::takeTurn()
{
	//bestMove();
	

}

//AiMove AI::bestMove(int t_player)
//{
//
//	//Check if Game is over
//	int rv;
//	//rv = board.checkVictory();
//
//	//AiWin
//	if (rv == m_AI_PLAYER) {
//		return AiMove(10);
//	}
//	//PlayerWin
//	else if (rv == m_HUMAN_PLAYER) {
//		return AiMove(-10);
//	}
//
//	std::vector<AiMove> moves;
//
//	//Go through all of the pieces
//	for (Pieces* piece : m_AIPieces)
//	{
//		//2.board(peg) return
//
//		//board.getPieceNeighbours(piece)
//
//		board.getNeighbours(piece);
//
//		//Get array of surrounding peg holes
//		std::vector<PegHoles*> adjacentPegHoles = piece.getNeighbours(); //<--------------------------------- NEED A FUNCTION TO RETURN VECTOR OF POINTERS TO PEG HOLES
//
//
//
//		//Go through each adjacent Hole
//		for (PegHoles* pegHole : adjacentPegHoles)
//		{
//			//Check Ocupied
//
//			if (pegHole->getPegOccupied()) //<----------------------------------------------- NEED FUNCTION RETURNING BOOL TO CHECK OCUPIED 
//			{
//				//Difference between two vectors
//
//				sf::Vector2f vectorToPeghole()
//
//
//				/*
//				PegHoles* pegHoleOver = pegHole.getPegHoleOver() // <----------------- NEED A FUNCTION RETURNING POINTER TO PEG HOLE THAT IS OVER THE CURRENT ONE
//
//				if(pegHoleOver.isOcupied)
//				{
//					//do nothing
//				}
//				else
//				{
//					if (t_player == m_AI_PLAYER) {
//                    move.score = getBestMove(m_HUMAN_PLAYER).score;
//					} 
//					else {
//                    move.score = getBestMove(m_AI_PLAYER).score;
//					}
//
//					AiMove availibleMove;
//					move.aiPiece = piece;
//					move.destinationPegHole = pegHoleOver;
//
//
//					moves.push_back(availibleMove)
//				}
//				*/
//			}
//			else()
//			{
//				if (t_player == m_AI_PLAYER) {
//					move.score = getBestMove(m_HUMAN_PLAYER).score;
//				}
//				else {
//					move.score = getBestMove(m_AI_PLAYER).score;
//				}
//
//				AiMove availibleMove;
//				move.aiPiece = piece;
//				move.destinationPegHole = pegHole;
//
//				moves.push_back(availibleMove)
//			}
//		}
//
//	}
//
//	// Pick the best move for the current player
//	int bestMove = 0;
//	if (t_player == m_AI_PLAYER) {
//		int bestScore = -1000000;
//		for (int i = 0; i < moves.size(); i++) {
//			if (moves[i].score > bestScore) {
//				bestMove = i;
//				bestScore = moves[i].score;
//			}
//		}
//	}
//	else {
//		int bestScore = 1000000;
//		for (int i = 0; i < moves.size(); i++) {
//			if (moves[i].score < bestScore) {
//				bestMove = i;
//				bestScore = moves[i].score;
//			}
//		}
//	}
//
//	return moves.at(bestMove);
//}


