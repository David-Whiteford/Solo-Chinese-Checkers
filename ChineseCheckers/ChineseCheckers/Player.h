#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collisions.h"
#include "Pieces.h"
#include "Board.h"
#include "AI.h"

class Player
{
public:
	Player();
	~Player();
	void movePiece(sf::RenderWindow& t_window);
	void setUpPieces(sf::RenderWindow& t_window, Board* t_board);
	void draw(sf::RenderWindow& t_window);
	void grabPiece(sf::RenderWindow& t_window);
	void placePiece();
	void checkEndRaysCol(std::vector<Raycast*> t_pegNeighbours);
	void pegOccupiedCheck();

private:
	Collisions m_colisions;
	Board* m_board;
	AI m_aiPieces;
	std::vector<Pieces*> m_playerPieces;
	int m_index = 0;
	bool m_sideTop = true;
	int m_doOnce = 0;
	int m_maxPlaces = 16;
	Raycast* m_jumpRay = new Raycast(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0);;
	std::vector<Raycast*> m_raysVec;
	std::vector<Raycast*> m_endRaysVec;
	std::vector<PegHoles*> m_neighboursVec;
	std::vector<PegHoles*> m_pegHolesVec;
	std::vector<Pieces*> m_aiPiecesVec;
	std::vector<Pieces*> m_allPieces;
	std::vector<PegHoles*> m_goalPegHoles;
	int m_pegRadius = 10;
	int m_pieceIndex = 11;
	int m_pegIndex = 0;
	bool piecePlaced = false;
	bool m_pieceHeld = false;
	bool m_moseButtonReleased = false;
	bool m_piecePlaced = false;
	bool m_positionFound = false;
	int m_currentPress = 0;
	std::vector<sf::Vector2f> m_resetPos;
	sf::Vector2f m_mousePos = sf::Vector2f(0, 0);
	sf::Vector2f m_newPiecePos = sf::Vector2f(0, 0);
	bool m_newPosFound = true;
	sf::Vector2f m_offset = sf::Vector2f(10, 10);
	sf::Vector2f m_newMousePos = sf::Vector2f(0, 0);
	bool m_insidePiece = false;
	int m_rayEndIndex = 0;
	int m_jumpAvailable = 0;

};

