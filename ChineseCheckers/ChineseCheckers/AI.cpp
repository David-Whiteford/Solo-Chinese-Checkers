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
	m_board = t_board;
	m_pegHolesVec = t_board->getBoardHoles();
	for (int i = t_board->getBoardHoles().size() - 1; i > t_board->getBoardHoles().size() - m_places -7;--i)
	{
		if (t_board->getBoardHoles()[i]->getColor() == sf::Color::Green) {}
		else
		{
			m_AIPieces.push_back(new Pieces(t_window, t_board->getBoardHoles()[i]->getPosition(), sf::Color::Red));
			m_startingHoles.push_back(*t_board->getBoardHoles()[i]);
		}
	}

	for (int i = 0; i < 16; i++)
	{
		if (t_board->getBoardHoles()[i]->getColor() == sf::Color::Green) {}
		else
		{
			m_goalPegHoles.push_back(t_board->getBoardHoles()[i]);
		}
	}
	m_board->setAllPieces(m_AIPieces);
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

	//Goal PegHoles
	/*
	for (PegHoles* peghole : m_goalPegHoles)
	{
		//peghole->changeColor(sf::Color::Yellow);
	}
	*/

	/*
	for (PegHoles* peghole : m_startingHoles)
	{
		peghole->changeColor(sf::Color::Cyan);
	}
	*/
	
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
	//Moves Vector
	std::vector<AiMove> moves;

	//See moves for all Pieces
	for (Pieces* piece : m_AIPieces)
	{
		//Store original pos
		sf::Vector2f originalPos = piece->getPosition();

		//vector of all adjacent peg Holes
		std::vector<PegHoles*> adjacentPegHoles;

		//Adjacent Peg Holes
		adjacentPegHoles = m_board->setNeighbours(piece);
		
		//Go through each adjacent Hole
		for (PegHoles* pegHole :adjacentPegHoles)
		{
			pegHole->changeColor(sf::Color::Magenta);

			//Create the move
			AiMove availibleMove;

			//std::cout << pegHole->getPegOccupied() << std::endl;

			//Check Ocupied
			if (pegHole->getPegOccupied())
			{
				piece->setPosition(pegHole->getPosition());

				//Get the neighbours of this peghole
				std::vector<PegHoles*> neighbourOfNeighbour = m_board->setNeighbours(piece);

				for (PegHoles *occupiedNeighbour : neighbourOfNeighbour)
				{
					if (occupiedNeighbour->getPegOccupied())
					{
						//do nothing
					}
					else
					{
						//Availible move
						availibleMove.aiPiece = piece;
						availibleMove.destinationPegHole = occupiedNeighbour;
						availibleMove.score = m_scoring(&availibleMove);
					}
				}
			}
			else
			{
				//Availible move
				availibleMove.aiPiece = piece;
				availibleMove.destinationPegHole = pegHole;
				availibleMove.score = m_scoring(&availibleMove);

			}

			//Perform Move
			piece->setPosition(pegHole->getPosition());

			//Reccursive call
			if (t_depth < MAX_DEPTH)
			{			
				if (t_player == m_AI_PLAYER) {
						availibleMove.score = bestMove(m_HUMAN_PLAYER, t_board, t_depth + 1).score;
					}
					else {
						availibleMove.score = bestMove(m_AI_PLAYER, t_board, t_depth + 1).score;
					}
				}
			//Undo Move
			piece->setPosition(originalPos);
			//Add Move to Moves
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
		score += 10;
	}
	else if (distanceTravelled >= 21)
	{
		score += 10;
	}
	else if (distanceTravelled > 20)
	{
		score += 2;
	}

	//Scoring Distance to End goal
	for (PegHoles* pegHole : m_goalPegHoles)
	{
		
		if (pegHole->getPegOccupied())
		{
			sf::Vector2f goalPos = pegHole->getPosition();
			sf::Vector2f distanceVecToGoal;
			sf::Vector2f oldDistanceVecToGoal;

			//Old position distance to goal
			oldDistanceVecToGoal.x = originalPos.x - goalPos.x;
			oldDistanceVecToGoal.y = originalPos.y - goalPos.y;

			float oldDistanceToGoal = std::sqrt(oldDistanceVecToGoal.x * oldDistanceVecToGoal.x + oldDistanceVecToGoal.y * oldDistanceVecToGoal.y);

			//New Position distance to goal
			distanceVecToGoal.x = destinationPos.x - goalPos.x;
			distanceVecToGoal.y = destinationPos.y - goalPos.y;

			float distanceToGoal = std::sqrt(distanceVecToGoal.x * distanceVecToGoal.x + distanceVecToGoal.y * distanceVecToGoal.y);

			//Score new distance being further away
			if (oldDistanceToGoal < distanceToGoal)
			{
				score -= 100;
			}

			//Score distance to goal
			
			if (distanceToGoal < 21)
			{
				score = 9;
			}
			else if (distanceToGoal < 41)
			{
				score += 8;
			}
			else if (distanceToGoal < 81)
			{
				score += 7;
			}
			
			if (distanceToGoal < 121)
			{
				score += 6;
			}

			
			else if (distanceToGoal < 161)
			{
				score += 5;
			}
			else if (distanceToGoal < 201)
			{
				score += 4;
			}
			else if (distanceToGoal < 241)
			{
				score += 3;
			}
			
			else if (distanceToGoal < 281)
			{
				score += 2;
			}
		}
		break;
	}

	//Scoring furthest back
	float y = 0;
	for (Pieces* piece : m_AIPieces)
	{
		if (piece->getPosition().y > y)
		{
			y = piece->getPosition().y;
		}
	}

	if (y == t_move->aiPiece->getPosition().y)
	{
		score += 10;
	}
	

	/*
	//Scoring Getting off Starting zone
	for (PegHoles startPeghole : m_startingHoles)
	{
		if (startPeghole.getPosition() == t_move->aiPiece->getPosition())
		{
			score += 1;
		}
	}
	*/

	return score;
}

std::vector<Pieces*> AI::getAIPieces()
{
	return m_AIPieces;
}
