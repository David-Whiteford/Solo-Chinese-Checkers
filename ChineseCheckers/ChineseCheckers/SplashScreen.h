#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"

class Splash
{
public:
	Splash();
	~Splash();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void loadTextures();

private:
	sf::Font m_font;
	sf::Text m_message;
	sf::Sprite s_splashScreen;
	sf::Texture s_splashScreenTexture;

	float m_timer = 0;
};