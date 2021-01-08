#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
class PegHoles : public GameObject
{
public:
	PegHoles(sf::RenderWindow& t_window, float size, sf::Vector2f pos, sf::Sprite t_sprite) :
		m_window(t_window)
	{
		m_sprites = t_sprite;
		m_sprites.setPosition(pos);
		//m_sprites.setOrigin(sf::Vector2f(size / 2, size / 2));
		m_pegHoles.setPosition(pos);
		m_pegHoles.setFillColor(sf::Color::White);
		m_pegHoles.setRadius(m_radius);
		
		
	}
	~PegHoles() {}
	sf::Sprite getSprite() { return m_sprites; }
	void setPosition(sf::Vector2f(t_pos)) { m_sprites.setPosition(t_pos); }
	sf::Vector2f getPosition()
	{
		return m_pegHoles.getPosition();
	}
	void draw() 
	{ 
		//m_window.draw(m_sprites);
		m_window.draw(m_pegHoles);
	}
	void setEmpty(bool t_empty)
	{
		m_empty = t_empty;
	}
	GameObject* myGameObject;

private:
	sf::CircleShape m_pegHoles;
	sf::RenderWindow& m_window;
	sf::Sprite m_sprites;
	bool m_empty = true;
	int m_radius = 10;

};
