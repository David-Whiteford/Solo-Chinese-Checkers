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
	for (int i = t_board->getBoardHoles().size() - 1; i > t_board->getBoardHoles().size() - m_places -7;--i)
	{
		if (t_board->getBoardHoles()[i]->getColor() == sf::Color::Green) {}
		else
		{
			m_AIPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i]->getPosition(), sf::Color::Red));
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
}

void AI::takeTurn()
{
	AiMove move = bestMove(1, *m_board, 0);

	move.aiPiece->setPosition(move.destinationPegHole->getPosition());

	GamePlay::m_currentTurn = Turn::Player;
}


AiMove AI::bestMove(int t_player, Board t_board, int t_depth = 0)
{
	std::vector<AiMove> moves;
	for (Pieces* piece : m_AIPieces)
	{
		sf::Vector2f originalPos = piece->getPosition();

		std::vector<PegHoles*> adjacentPegHoles;

		//Adjacent Peg Holes
		adjacentPegHoles = m_board->setNeighbours(piece);

		
		//Go through each adjacent Hole
		for (PegHoles* pegHole :adjacentPegHoles)
		{
			//pegHole->changeColor(sf::Color::Magenta);

			//Create the move
			AiMove availibleMove;

			//Check Ocupied
			if (pegHole->getPegOccupied())
			{
				//do nothing
			}
			else
			{

				availibleMove.aiPiece = piece;
				availibleMove.destinationPegHole = pegHole;
				availibleMove.score = m_scoring(&availibleMove);

				//Perform Move
				piece->setPosition(pegHole->getPosition());
				//availibleMove.score = rand() % 300;
			}
			
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

		adjacentPegHoles.clear();
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

int AI::m_scoring(AiMove* t_move)
{
	//Score
	int score = 0;

	//Distance Travelled
	//Starting Vectors
	sf::Vector2f originalPos =  t_move->aiPiece->getPosition();
	sf::Vector2f destinationPos = t_move->destinationPegHole->getPosition();
	sf::Vector2f vectorTravelled;
	//Distance as float
	vectorTravelled.x = originalPos.x - destinationPos.x;
	vectorTravelled.y = originalPos.y - destinationPos.y;
	float distanceTravelled = std::sqrt(vectorTravelled.x * vectorTravelled.x + vectorTravelled.y * vectorTravelled.y);
	//Scoring Distance Travlled
	if (distanceTravelled >= 60)
	{
		score += 5;
		std::cout << "Checking " << std::endl;
	}
	else if (distanceTravelled >= 40)
	{
		score += 3;
	}
	else if (distanceTravelled > 20)
	{
		score += 1;
	}

	//Distance to End goal
	//sf::Vector2f destinationPos;





	return score;
}


