#include "Vector.h"

MyVector2::MyVector2()
{
}

MyVector2::~MyVector2()
{
}

MyVector2::MyVector2(double x, double y)
{
}
double MyVector2::length(sf::Vector2f t_pos) const
{
	//math to determine the lenght of the vector
	const double answer = std::sqrt(t_pos.x * t_pos.x + t_pos.y * t_pos.y);
	return answer;
}
sf::Vector2f MyVector2::normalise(sf::Vector2f t_pos)
{
	double vecLength = length(t_pos);

	if (vecLength != 0.0)
	{
		t_pos.x = t_pos.x / vecLength;
		t_pos.y = t_pos.y / vecLength;
	}
	return t_pos;
}

