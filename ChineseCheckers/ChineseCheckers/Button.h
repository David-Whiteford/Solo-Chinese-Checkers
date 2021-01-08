#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Globals.h"


class Button
{
public:
	Button();
	~Button();
	void setInfo(std::string t_string, float t_height, float t_width, sf::Vector2f t_pos);
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void setSize(int t_size);
	void loadTextures();

	void setSelected(bool t_selected);
	bool getSelected() { return m_selected; };

private:
	//Font Text for rendering
	sf::Font m_font;
	sf::Text m_text;
	sf::Color m_textColor;
	std::string m_string;
	//Position
	float m_height;
	float m_width;
	//Button Box
	sf::RectangleShape m_button;
	sf::Color m_colorRect;
	sf::Vector2f m_pos;

	//Selected
	bool m_selected = false;
	bool m_drawOutline = false;
};
