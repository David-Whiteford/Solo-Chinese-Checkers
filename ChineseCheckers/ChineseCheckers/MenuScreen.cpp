#include "MenuScreen.h"
#include "Game.h"
Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::update(sf::Time t_deltaTime)
{
	input(t_deltaTime);


	//Update Buttons
	for (Button button : buttons)
	{
		button.update(t_deltaTime);
	}

	for (Button difficultyButton : m_difficultyButtons)
	{
		difficultyButton.update(t_deltaTime);
	}

}

void Menu::render(sf::RenderWindow& t_window)
{
	m_currentButtonSelect();
	m_currentDifficultySelected();

	//Render Buttons
	for (Button button : buttons)
	{
		button.render(t_window);
	}

	switch (m_currentMode)
	{
	case menuButtons::playGame:
		t_window.draw(m_startGameText);
		break;
	case menuButtons::howToPlay:
		t_window.draw(m_howToPlayText);
		break;
	case menuButtons::options:
		for (Button difficultyButton : m_difficultyButtons)
		{
			difficultyButton.render(t_window);
		}
		break;
	case menuButtons::exit:
		t_window.draw(m_exitText);
		break;
	default:
		break;
	}
}

void Menu::setup(sf::Font& t_font)
{
	m_font = t_font;
	//Render Buttons
	for (Button button : buttons)
	{
		button.setup(t_font);
	}

	//Set up each button
	m_playButtonSetUp();
	m_howToPlaySetUp();
	m_optionsSetUp();
	m_exitSetUp();

	//Set up each Difficulty Button
	m_easyButtonSetUp();
	m_normalButtonSetUp();
	m_hardButtonSetUp();
}

void Menu::loadTextures()
{
}

void Menu::m_playButtonSetUp()
{
	buttons.at(0).setInfo("Play", 100, 30, sf::Vector2f(buttonX, buttonY));
	m_startGameText.setString(startString);
	m_startGameText.setCharacterSize(30);
	m_startGameText.setFillColor(sf::Color::White);
	m_startGameText.setPosition(10, 100);
	m_startGameText.setFont(m_font);
}

void Menu::m_howToPlaySetUp()
{
	buttons.at(1).setInfo("How to Play", 100, 30, sf::Vector2f(buttonX, buttonY * 2));
	m_howToPlayText.setString(howToPlayString);
	m_howToPlayText.setCharacterSize(30);
	m_howToPlayText.setFillColor(sf::Color::White);
	m_howToPlayText.setPosition(10, 10);
	m_howToPlayText.setFont(m_font);
}

void Menu::m_optionsSetUp()
{
	buttons.at(2).setInfo("Difficulty", 100, 30, sf::Vector2f(buttonX, buttonY * 3));
}

void Menu::m_exitSetUp()
{
	buttons.at(3).setInfo("Exit", 100, 30, sf::Vector2f(buttonX, buttonY * 4));
}

void Menu::m_currentButtonSelect()
{
	switch (m_currentMode)
	{
	case menuButtons::playGame:
		buttons.at(0).setSelected(true);
		buttons.at(1).setSelected(false);
		buttons.at(2).setSelected(false);
		buttons.at(3).setSelected(false);
		break;
	case menuButtons::howToPlay:
		buttons.at(0).setSelected(false);
		buttons.at(1).setSelected(true);
		buttons.at(2).setSelected(false);
		buttons.at(3).setSelected(false);
		break;
	case menuButtons::options:
		buttons.at(0).setSelected(false);
		buttons.at(1).setSelected(false);
		buttons.at(2).setSelected(true);
		buttons.at(3).setSelected(false);
		break;
	case menuButtons::exit:
		buttons.at(0).setSelected(false);
		buttons.at(1).setSelected(false);
		buttons.at(2).setSelected(false);
		buttons.at(3).setSelected(true);
		break;
	default:
		break;
	}
}

void Menu::input(sf::Time t_deltaTime)
{
	if (m_timer < m_minWaitForTime)
	{
		m_timer += t_deltaTime.asMilliseconds();
	}

	if (m_timer >= m_minWaitForTime)
	{
		//Navigate Menu Down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (static_cast<int>(m_currentMode) < m_ammountOfButtons)
			{
				m_currentMode = static_cast<menuButtons>(static_cast<int>(m_currentMode) + 1);
			}
			else
			{
				m_currentMode = static_cast<menuButtons>(0);
			}
			m_timer = 0;
		}
		//Navigate Menu Up
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (static_cast<int>(m_currentMode) <= 0)
			{
				m_currentMode = static_cast<menuButtons>(m_ammountOfButtons);
			}
			else
			{
				m_currentMode = static_cast<menuButtons>(static_cast<int>(m_currentMode) - 1);
			}

			m_timer = 0;
		}

		//Difficulty Options Left to Right
		if (m_currentMode == menuButtons::options)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (static_cast<int>(Game::m_difficulty) < m_amountOfDifficultyOptions)
				{
					Game::m_difficulty = static_cast<Difficulty>(static_cast<int>(Game::m_difficulty) + 1);
				}
				else
				{
					Game::m_difficulty = static_cast<Difficulty>(0);
				}
				m_timer = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (static_cast<int>(Game::m_difficulty) > 0)
				{
					Game::m_difficulty = static_cast<Difficulty>(static_cast<int>(Game::m_difficulty) - 1);
				}
				else
				{
					Game::m_difficulty = static_cast<Difficulty>(m_amountOfDifficultyOptions);
				}
				m_timer = 0;
			}
		}
	}


	//Select
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		switch (m_currentMode)
		{
		case menuButtons::playGame:
			Game::m_currentMode = GameMode::Gameplay;
			break;
		case menuButtons::exit:
			
			break;
		default:
			break;
		}
	}

}

void Menu::display()
{


}

void Menu::m_currentDifficultySelected()
{
	switch (Game::m_difficulty)
	{
	case Difficulty::Easy:
		m_difficultyButtons.at(0).setSelected(true);
		m_difficultyButtons.at(1).setSelected(false);
		m_difficultyButtons.at(2).setSelected(false);
		Game::m_difficulty = Difficulty::Easy;
		break;
	case Difficulty::Medium:
		m_difficultyButtons.at(0).setSelected(false);
		m_difficultyButtons.at(1).setSelected(true);
		m_difficultyButtons.at(2).setSelected(false);
		Game::m_difficulty = Difficulty::Medium;
		break;
	case Difficulty::Hard:
		m_difficultyButtons.at(0).setSelected(false);
		m_difficultyButtons.at(1).setSelected(false);
		m_difficultyButtons.at(2).setSelected(true);
		Game::m_difficulty = Difficulty::Hard;
		break;
	}
}


void Menu::m_easyButtonSetUp()
{
	m_difficultyButtons.at(0).setInfo("Easy", 100, 30, sf::Vector2f(20, 100));
}

void Menu::m_normalButtonSetUp()
{
	m_difficultyButtons.at(1).setInfo("Normal", 100, 30, sf::Vector2f(140, 100));
}

void Menu::m_hardButtonSetUp()
{
	m_difficultyButtons.at(2).setInfo("Hard", 100, 30, sf::Vector2f(260, 100));
}
