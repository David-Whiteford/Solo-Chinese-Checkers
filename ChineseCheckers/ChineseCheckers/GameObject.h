#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
//tags for the player and the ai (Can add more if needed)
const int PLAYER_TAG = 0, AI_TAG = 1;

class GameObject
{
public:
	GameObject() { static int _id; id = _id++; }

	virtual ~GameObject() {}

	void setTag(sf::String t_tag) { m_tag = t_tag; }
	sf::String getTag() { return m_tag; }

	sf::Vector2f position;
	float size;

	int id;


private:
	sf::String m_tag;
};
