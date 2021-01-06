#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
class Pieces : public GameObject
{
public:
	Pieces(sf::RenderWindow& t_window, sf::Vector2f pos,sf::Color t_pieceColor) :
		m_window(t_window)
	{
		m_piece.setPosition(pos);
		m_piece.setFillColor(t_pieceColor);
		m_piece.setRadius(10);
		
	}
	~Pieces() {}
	sf::Sprite getSprite() { 
		return m_sprites;
	}
	void setPosition(sf::Vector2f(t_pos)) { 
		m_sprites.setPosition(t_pos); 
	}
	void draw()
	{
		m_window.draw(m_piece);
	}
private:
	sf::CircleShape m_piece;
	sf::RenderWindow& m_window;
	sf::Sprite m_sprites;

};
