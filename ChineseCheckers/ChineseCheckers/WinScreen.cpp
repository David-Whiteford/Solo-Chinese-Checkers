#include "WinScreen.h"
#include "Game.h"

Win::Win()
{
}

Win::~Win()
{
}

void Win::update(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		Game::m_currentMode = GameMode::Menu;
	}
}

void Win::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_winText);
	m_returnToMenu.render(t_window);
}

void Win::setup(sf::Font& t_font)
{
	m_font = t_font;

	m_winText.setFillColor(sf::Color::White);
	m_winText.setCharacterSize(20);
	m_winText.setFont(m_font);
	m_winText.setString(m_winString);
	m_winText.setPosition(200, 180);

	m_returnToMenu.setInfo("Return To Menu", 120,30, sf::Vector2f(250, SCREEN_HEIGHT - 100));
	m_returnToMenu.setSelected(true);

}

void Win::loadTextures()
{
}
