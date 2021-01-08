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

	/*void setTeamTag(sf::String t_tag) { m_tag = t_tag; }
	sf::String getTeamTag() { return m_tag; }
	
	void setPegOccupied(bool t_pegOccupied) { m_pegOccupied = t_pegOccupied; }
	bool getPegOccupied() { return m_pegOccupied; }*/

	sf::Vector2f position;
	float size;

	int id;


private:
	/*sf::String m_tag;
	bool m_pegOccupied = false;*/
};
