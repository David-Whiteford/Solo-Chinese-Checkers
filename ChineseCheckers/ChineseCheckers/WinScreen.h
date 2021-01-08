#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Button.h"

class Win
{
public:
	Win();
	~Win();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void loadTextures();

private:
	//Wub Sprite
	sf::Sprite m_winScreen;
	sf::Texture m_winScreenTexture;

	//Text
	sf::Font m_font;
	sf::Text m_winText;
	std::string m_winString = "Congratulations you have Won!\n Press Enter to return to Menu";

	//Button
	Button m_returnToMenu;

};