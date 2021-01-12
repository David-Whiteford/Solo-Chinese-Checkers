#include "Collisions.h"

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
}

bool Collisions::pointCircleCol(sf::Vector2f t_point, sf::Vector2f t_circle,  int t_radius)
{
	if (t_point.x < t_circle.x + t_radius * 2
		&& t_point.x  > t_circle.x
		&& t_point.y < t_circle.y + t_radius * 2
		&& t_point.y > t_circle.y)
	{
		return true;
	}
	else
	{
		return false; 
	}
	
}

bool Collisions::circleToCircleCol(sf::Vector2f t_circle1, sf::Vector2f t_circle2, int t_circleOneRadius, int t_circleTwoRadius)
{
	return false;
}
