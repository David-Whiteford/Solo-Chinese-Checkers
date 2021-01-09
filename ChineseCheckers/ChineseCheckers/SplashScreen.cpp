#include "SplashScreen.h"
#include "Game.h"

Splash::Splash()
{
}

Splash::~Splash()
{
}

void Splash::update(sf::Time t_deltaTime)
{
	m_timer = m_timer + t_deltaTime.asSeconds();

	if (m_timer >= 3)
	{
		Game::m_currentMode = GameMode::Menu;
	}
}

void Splash::render(sf::RenderWindow& t_window)
{
	t_window.draw(s_splashScreen);
}

void Splash::setup(sf::Font& t_font)
{
	loadTextures();
	s_splashScreen.setTexture(s_splashScreenTexture);
}

void Splash::loadTextures()
{

	if (!s_splashScreenTexture.loadFromFile("Assets/Images/splashscreen.jpg"))
	{
		std::cout << "Error loading splash screen" << std::endl;
	}
}
