#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include "Player.h"
#include "Board.h"
class GamePlay
{
public:
	GamePlay();
	~GamePlay();
	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font, sf::RenderWindow& t_window,Board* t_board);
	void initialise();
private:
	//Font
	sf::Font m_font;
	Player m_player;


};