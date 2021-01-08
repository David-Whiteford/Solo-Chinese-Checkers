#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Button.h"
#include <array>

enum class loseMenuButtons {
	playGame,
	returnToMenu
};

class Lose
{
public:
	Lose();
	~Lose();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void loadTextures();

private:
	//Lose Sprite
	sf::Sprite m_winScreen;
	sf::Texture m_winScreenTexture;

	//Text
	sf::Font m_font;
	sf::Text m_loseText;
	std::string m_loseString = "Unlucky! You Lost!\n";

	//Button
	static const int m_amountButtons = 2;
	 std::array<Button, m_amountButtons> m_buttons;

	 loseMenuButtons m_currentMode{ loseMenuButtons::playGame };

	 //Input
	 void input(sf::Time t_deltaTime);
	 float m_timer = 0;
	 float m_minWaitForTime = 250;

	 void currentButtonSelected();
};