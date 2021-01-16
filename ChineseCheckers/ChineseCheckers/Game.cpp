#include "Game.h"

GameMode Game::m_currentMode{ GameMode::Splash };
Difficulty Game::m_difficulty{ Difficulty::Easy };

Game::Game() : m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32 }, "Chinese Checkers by Tom Lloyd and David Whiteford" }, m_exitGame{ false }
{
	
	setupAssets();
	
}

Game::~Game()
{
	srand(time(NULL));
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			render();
		}
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if ((sf::Keyboard::Escape == event.key.code) && (Game::m_currentMode == GameMode::Gameplay))
			{
				//Pause
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentMode)
	{
	case GameMode::Splash:
		m_splashScreen.update(t_deltaTime);
		break;
	case GameMode::Menu:
		m_menu.update(t_deltaTime);
		break;
	case GameMode::Gameplay:
		m_gameplayScreen.update(t_deltaTime, m_window);
		break;
	case GameMode::Win:
		m_winScreen.update(t_deltaTime);
		break;
	case GameMode::Lose:
		m_loseScreen.update(t_deltaTime);
		break;
	default:
		break;
	}

	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	switch (m_currentMode)
	{
	case GameMode::Splash:
		m_splashScreen.render(m_window);
		break;
	case GameMode::Menu:
		m_menu.render(m_window);
		break;
	case GameMode::Gameplay:
	
		m_gameplayScreen.render(m_window);
		break;
	case GameMode::Win:
		m_winScreen.render(m_window);
		break;
	case GameMode::Lose:
		m_loseScreen.render(m_window);
		break;
	default:
		break;
	}

	m_window.display();
}

void Game::setupAssets()
{
	//Setting up Font
	if (!m_ArialBlackfont.loadFromFile("Assets/Fonts/QuickSmart.otf"))
	{
		//std::cout << "problem loading arial Stardust Font" << std::endl;
	}
	m_gameplayScreen.setup(m_ArialBlackfont,m_window);
	m_splashScreen.setup(m_ArialBlackfont);
	m_menu.setup(m_ArialBlackfont);
	m_winScreen.setup(m_ArialBlackfont);
	m_loseScreen.setup(m_ArialBlackfont);
	
}

