#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>

class Raycast
{

public:
	Raycast(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length);
	~Raycast();
	void setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length);
	sf::Vector2f getRayStartPos()
	{
		return m_positon;
	}
	sf::Vector2f getDirection()
	{
		return m_direction;
	}
	float getRayLength()
	{
		return m_rayLength;
	}

	bool hit(sf::Vector2f t_targetPosition, float t_targetRadius);
	sf::VertexArray drawRay();
	bool isInterpolating();
	sf::Vector2f getEndPoint();

private:
	float m_rayLength = 1000;
	sf::Vector2f m_direction;
	sf::Vector2f m_positon;

	sf::Vertex m_raycastLine[2];

	bool interpolate = false;



	//bool raycastHit = false;


};