#include "LoseScreen.h"
#include "Game.h"

Lose::Lose()
{
}

Lose::~Lose()
{
}

void Lose::update(sf::Time t_deltaTime)
{
	input(t_deltaTime);
	currentButtonSelected();
}

void Lose::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_loseText);
	for (Button button : m_buttons)
	{
		button.render(t_window);
	}
}

void Lose::setup(sf::Font& t_font)
{
	m_font = t_font;

	//Lost Text
	m_loseText.setFillColor(sf::Color::White);
	m_loseText.setCharacterSize(20);
	m_loseText.setFont(m_font);
	m_loseText.setString(m_loseString);
	m_loseText.setPosition(200, 180);

	//Buttons
	m_buttons.at(0).setInfo("Play Again", 100, 30, sf::Vector2f(200, 400));
	m_buttons.at(1).setInfo("Main Menu", 100, 30, sf::Vector2f(350, 400));

}

void Lose::loadTextures()
{
}

void Lose::input(sf::Time t_deltaTime)
{
	if (m_timer < m_minWaitForTime)
	{
		m_timer += t_deltaTime.asMilliseconds();
	}



	if (m_timer >= m_minWaitForTime)
	{
		//Navigate Menu Right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (static_cast<int>(m_currentMode) < m_amountButtons)
			{
				m_currentMode = static_cast<loseMenuButtons>(static_cast<int>(m_currentMode) + 1);
			}
			else
			{
				m_currentMode = static_cast<loseMenuButtons>(0);
			}
			m_timer = 0;
		}
		//Navigate Menu Left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (static_cast<int>(m_currentMode) <= 0)
			{
				m_currentMode = static_cast<loseMenuButtons>(m_amountButtons);
			}
			else
			{
				m_currentMode = static_cast<loseMenuButtons>(static_cast<int>(m_currentMode) - 1);
			}

			m_timer = 0;
		}
	}

	//Select
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		switch (m_currentMode)
		{
		case loseMenuButtons::playGame:
			Game::m_currentMode = GameMode::Gameplay;
			break;
		case loseMenuButtons::returnToMenu:
			Game::m_currentMode = GameMode::Menu;
			break;
		default:
			break;
		}
	}

}

void Lose::currentButtonSelected()
{
	switch (m_currentMode)
	{
	case loseMenuButtons::playGame:
		m_buttons.at(0).setSelected(true);
		m_buttons.at(1).setSelected(false);
		break;
	case loseMenuButtons::returnToMenu:
		m_buttons.at(0).setSelected(false);
		m_buttons.at(1).setSelected(true);
		break;
	default:
		break;
	}
}
