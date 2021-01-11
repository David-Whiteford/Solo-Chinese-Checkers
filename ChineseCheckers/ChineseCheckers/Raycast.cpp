#include "Raycast.h"
Raycast::Raycast(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length)
{
	interpolate = true;
	m_positon = t_startPosition;
	m_direction = -t_direction;
	m_rayLength = t_length;
}

Raycast::~Raycast()
{
}

void Raycast::setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length)
{
	m_positon = t_startPosition;
	m_direction = -t_direction;
	m_rayLength = t_length;
}

sf::VertexArray Raycast::drawRay()
{
	sf::VertexArray ray(sf::LinesStrip, 2);
	ray[0].position = m_positon;
	ray[0].color = sf::Color::Red;
	ray[1].position = m_positon + (m_direction * (m_rayLength));
	ray[1].color = sf::Color::Red;
	return ray;
}
bool Raycast::isInterpolating()
{
	return interpolate;
}
sf::Vector2f Raycast::getEndPoint()
{
	return m_positon + (m_direction * m_rayLength);
}