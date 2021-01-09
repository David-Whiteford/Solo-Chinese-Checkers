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
		m_pegHolesVec[i]->draw();
	}
	for (int i = 0; i < m_raysVec.size(); ++i)
	{
		t_window.draw(m_raysVec[i]->drawRay());
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
			//std::cout << "2D Array Vals: " << m_gameBoard[row][col] << std::endl;
			type = m_gameBoard[row][col];
			switch (type)
			{
			case 0:
				break;
			case 1:
				m_pegHolesVec.push_back(new PegHoles(t_window, m_tileSize,
					sf::Vector2f(x * m_tileSize, y * m_tileSize), m_pegSprite, sf::Color::White));
				m_raysVec.push_back(new Raycast());
				m_raysVec.back()->setRayValues(sf::Vector2f(x * m_tileSize + 10, y * m_tileSize + 10), sf::Vector2f(10, 10),3);
				
			
				break;
			default:
				break;
			}
			x++;
			if (x == m_mapWidth)
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

void Board::setUpRays()
{
	
}

