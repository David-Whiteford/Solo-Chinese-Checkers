#pragma once
#include "GameObject.h"
#include "PegHoles.h"
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
		m_piece.setRadius(m_radius);
	}
	~Pieces() {}
	sf::Sprite getSprite() { 
		return m_sprites;
	}
	void setPosition(sf::Vector2f(t_pos)) { 
		m_piece.setPosition(t_pos); 
	}
	sf::Vector2f getPosition()
	{
		return m_piece.getPosition();
	}
	void setNeighbours(PegHoles* t_neighbourPegs)
	{
		m_neighboursPegs.push_back(t_neighbourPegs);
	}
	std::vector<PegHoles*> getNeighbours()
	{
		return m_neighboursPegs;
	}
	void draw()
	{
		m_window.draw(m_piece);
	}
private:
	sf::CircleShape m_piece;
	sf::RenderWindow& m_window;
	sf::Sprite m_sprites;
	int m_radius = 10;
	std::vector<PegHoles*> m_neighboursPegs;
	
};
