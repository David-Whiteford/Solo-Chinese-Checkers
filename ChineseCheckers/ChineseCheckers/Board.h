#ifndef BOARD_H
#define BOARD_H


#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PegHoles.h"

class Board
{
public:
	Board();
	~Board();
	void LoadBoard(int arr[21][20]);
	void Draw();
	void init();
	void setMap(sf::RenderWindow& t_window);
	std::vector<PegHoles*> getBoardHoles();
private:
	sf::Texture m_texture;
	int m_gameBoard[21][20];
	int m_boardWidth = 21;
	int m_boardHeigth = 20;
	sf::Sprite m_pegSprite;
	static const int m_mapWidth = 21;
	static const int m_mapHeigth = 20;
	std::vector<PegHoles*> m_pegHolesVec;
	int m_tileSize = 20;
	int lvl1[m_mapWidth][m_mapHeigth] = {
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,
0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
};
#endif