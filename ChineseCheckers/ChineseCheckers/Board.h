#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "PegHoles.h"
#include "Raycast.h"
#include "Vector.h"
#include "Collisions.h"
#include "Pieces.h"
int const ROWS = 21;
int const COLS = 20;
class Board
{
public:
	Board();
	~Board();
	void LoadBoard(int arr[21][20]);
	void Draw(sf::RenderWindow& t_window);
	void init();
	void setMap(sf::RenderWindow& t_window);
	std::vector<PegHoles*> getBoardHoles();
	std::vector<Raycast*> getRays();
	void setUpRays();
	//PegHoles* getPegHole(Raycast* t_ray);
	//std::vector<PegHoles*> getPieceNeigthbours(Pieces* t_piece);
	std::vector<PegHoles*> setNeighbours(Pieces* t_piece);
	void setPegHoleOccupied(std::vector<Pieces*> t_pieces);
private:
	Collisions m_colisions;
	float m_maxDist = 40.0f;
	MyVector2 m_vector2;
	sf::Texture m_texture;
	int m_gameBoard[21][20];
	int m_boardWidth = 21;
	int m_boardHeigth = 20;
	sf::Sprite m_pegSprite;
	std::vector<PegHoles*> m_pegHolesVec;
	std::vector<Raycast*> m_raysVec;
	std::vector<Raycast*> m_neighboursRaysVec;
	std::vector<PegHoles*> m_pieceNeighbours;
	sf::Vector2f m_offset = sf::Vector2f(10, 10);
	int m_radius = 10;
	int m_tileSize = 20;
	int lvl1[ROWS][COLS] = {
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,2,1,2,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,2,1,2,1,2,1,0,0,0,0,0,0,0,
1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,
0,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,0,
0,0,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,0,0,
0,0,0,0,1,2,1,2,1,2,1,2,1,2,1,2,1,0,0,0,0,
0,0,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,0,0,
0,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,0,
0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,
1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
0,0,0,0,0,0,0,1,2,1,2,1,2,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,2,1,2,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
};
#endif