#include "Board.h"

Board::Board()
{
	init();
	LoadBoard(lvl1);
}

Board::~Board()
{
}

void Board::LoadBoard(int arr[21][20])
{
	for (int row = 0; row < m_boardWidth; row++)
	{
		for (int col = 0; col < m_boardHeigth; col++)
		{
			m_gameBoard[row][col] = arr[row][col];
		}
	}
}


void Board::Draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_pegHolesVec.size(); ++i)
	{
		if (m_pegHolesVec[i]->getColor() == sf::Color::Green){}
		else
		{
			m_pegHolesVec[i]->draw();
		}
	}
}

void Board::init()
{
	if (!m_texture.loadFromFile("IMAGES//.png"))
	{
		// error...
	}
	m_pegSprite.setTexture(m_texture);
	m_pegSprite.setTextureRect(sf::IntRect(128, 352, 16, 16));
}

void Board::setMap(sf::RenderWindow& t_window)
{
	int type = 0;
	int x = 0;
	int y = 0;
	for (int row = 0; row < m_boardWidth; row++)
	{
		for (int col = 0; col < m_boardHeigth; col++)
		{
			
			type = m_gameBoard[row][col];
			switch (type)
			{
			case 0:
				break;
			case 1:
				m_pegHolesVec.push_back(new PegHoles(t_window, m_tileSize,
					sf::Vector2f(x * m_tileSize, y * m_tileSize), m_pegSprite, sf::Color::White , y , x));	
				break;
			case 2:
				m_pegHolesVec.push_back(new PegHoles(t_window, m_tileSize,
					sf::Vector2f(x * m_tileSize, y * m_tileSize), m_pegSprite, sf::Color::Green, y, x));
				break;
			default:
				break;
			}
			x++;
			if (x == ROWS)
			{
				x = 0;
				y++;
			}
		}
	}
}

std::vector<PegHoles*> Board::getBoardHoles() 
{
	return m_pegHolesVec;
}
std::vector<Raycast*> Board::getRays()
{
	return m_raysVec;
}
void Board::setUpRays()
{
	float distance;
	int rayLength = 28;
	for (int i = 0; i < m_pegHolesVec.size();i++)
	{
		for (int direction = 0; direction < 9; direction++)
		{
			if (direction == 4) continue; // Skip 4, this is ourself.
			
			int n_row = m_pegHolesVec[i]->getRow() + ((direction % 3) - 1); // Neighbor row
			int n_col = m_pegHolesVec[i]->getCol() + ((direction / 3) - 1); // Neighbor column
			
			if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
			{
				for (int j = 0; j < m_pegHolesVec.size(); j++)
				{
					if (m_pegHolesVec[j]->getRow() == n_row && m_pegHolesVec[j]->getCol() == n_col)
					{
						//get the startposition and the end position of the ray. These are at a peg in the peg hole
						//vector and its neighbours.
						sf::Vector2f startPos = sf::Vector2f(m_pegHolesVec[i]->getPosition().x + 10
							,m_pegHolesVec[i]->getPosition().y + 10);
						sf::Vector2f endPos = sf::Vector2f(m_pegHolesVec[j]->getPosition().x + 10
							, m_pegHolesVec[j]->getPosition().y + 10);
						m_pegHolesVec[i]->setNeighbours(m_pegHolesVec[j]);
						//std::cout << "Neighbours: " << m_pegHolesVec[i]->getNeighbours().size() << std::endl;
						//get the direction of the ray and normalise it
						sf::Vector2f directionVec = startPos - endPos;
						sf::Vector2f newDir = m_vector2.normalise(directionVec);
						//get the distance from the start position of the ray to the end position
						//this is depending on the direction of the ray
						if (newDir.x == 1 || newDir.x == -1 ||
							newDir.y == 1 || newDir.y == -1)
						{
							distance = m_maxDist;
						}
						else
						{
							distance = sqrt(((startPos.x - endPos.x) * (startPos.x - endPos.x))
								+ (startPos.y - endPos.y) * (startPos.y - endPos.y));
							//creates a new ray and pushs it to a vector to be stored
							m_raysVec.push_back(new Raycast(startPos, newDir, distance));
						}
					}
				}
			}
		}
	}
}

std::vector<PegHoles*> Board::setNeighbours(Pieces* t_piece)
{

	m_neighboursVec.clear();
	m_neighboursRaysVec.clear();

	for (int i = 0; i < m_raysVec.size(); i++)
	{
		if (m_colisions.pointCircleCol(m_raysVec[i]->getRayStartPos(), t_piece->getPosition(), m_radius))
		{
			m_neighboursRaysVec.push_back(m_raysVec[i]);
		}
	}
	for (int i = 0; i < m_pegHolesVec.size(); i++)
	{
		for (int j = 0; j < m_neighboursRaysVec.size(); j++)
		{
			if (m_colisions.pointCircleCol(m_neighboursRaysVec[j]->getEndPoint(), m_pegHolesVec[i]->getPosition(), m_radius))
			{
				m_neighboursVec.push_back(m_pegHolesVec[i]);
				//t_piece->setNeighbours(m_neighboursVec);
			}
		}
	}

	m_neighboursRaysVec.clear();
	return m_neighboursVec;


}

void Board::setPegHoleOccupied(std::vector<Pieces*> t_pieces, std::vector<Pieces*> t_aiPieces)
{
	//Player
	t_pieces.insert(t_pieces.end(), t_aiPieces.begin(), t_aiPieces.end());
	for (int j = 0; j < m_pegHolesVec.size(); j++)
	{
		for (int i = 0; i < t_pieces.size(); i++)
		{
			if (m_colisions.pointCircleCol(t_pieces[i]->getPosition() + m_offset,
				m_pegHolesVec[j]->getPosition(), m_radius) == false)
			{
				m_pegHolesVec[j]->setPegOccupied(false);
				m_pegHolesVec[j]->setTeamTag("White");
			}
			else if (m_colisions.pointCircleCol(t_pieces[i]->getPosition() + m_offset,
				m_pegHolesVec[j]->getPosition(), m_radius) == true)
			{
				m_pegHolesVec[j]->setPegOccupied(true);
				m_pegHolesVec[j]->setTeamTag("Blue");
				break;
			}
		}
	}
	//t_pieces.clear();

	/*
	for (int i = 0; i < t_pieces.size(); i++)
	{
		for (int j = 0; j < m_pegHolesVec.size(); j++)
		{
			if (m_colisions.pointCircleCol(t_pieces[i]->getPosition() + m_offset,
				m_pegHolesVec[j]->getPosition(), m_radius) == false)
			{
				m_pegHolesVec[j]->setPegOccupied(false);
				m_pegHolesVec[j]->setTeamTag("White");
			}
			else if (m_colisions.pointCircleCol(t_pieces[i]->getPosition() + m_offset,
				m_pegHolesVec[j]->getPosition(), m_radius) == true)
			{
				m_pegHolesVec[j]->setPegOccupied(true);
				m_pegHolesVec[j]->setTeamTag("Blue");
			}
		}
	}
	*/
}
std::vector<Raycast*> Board::setNeighboursRays(Pieces* t_piece)
{
	m_neighboursRaysVec.clear();
	for (int i = 0; i < m_raysVec.size(); i++)
	{
		if (m_colisions.pointCircleCol(m_raysVec[i]->getRayStartPos(), t_piece->getPosition(), m_radius))
		{
			m_neighboursRaysVec.push_back(m_raysVec[i]);
		}
	}

	return m_neighboursRaysVec;
}

void Board::setAllPieces(std::vector<Pieces*> t_pieces)
{
	for (Pieces* pieces : t_pieces)
	{
		m_allPiece.push_back(pieces);
	}
}

std::vector<Pieces*> Board::getAllPieces()
{
	return m_allPiece;
}
std::vector<Raycast*> Board::pegOccupiedCheck(Pieces* t_currentPiece, std::vector<Pieces*> t_pieces)
{
	m_endRaysVec.clear();
	for (int i = 0; i < t_pieces.size(); i++)
	{
		for (int j = 0; j < m_allPiece.size(); j++)
		{
			if (i == j) {}
			else
			{
				if (m_colisions.pointCircleCol(t_pieces[i]->getPosition() + m_offset,
					m_allPiece[j]->getPosition(), m_radius))
				{
					if (m_jumpAvailable == 0)
					{
						m_endRaysVec = setNeighboursRays(t_currentPiece);
						m_jumpAvailable++;

					}
				}
			}

		}
	}
	m_jumpAvailable = 0;
	return m_endRaysVec;
}

void Board::clearNeighbours()
{

}
