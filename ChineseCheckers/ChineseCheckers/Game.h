#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include "Globals.h"
#include "Board.h"
#include "SplashScreen.h"
#include "MenuScreen.h"
#include "WinScreen.h"
#include "LoseScreen.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	static GameMode m_currentMode;
	static Difficulty m_difficulty;

private:
	//Game Loop
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setupAssets();
	//Board* m_board;
	//Font
	sf::Font m_ArialBlackfont;

	//Screens
	sf::RenderWindow m_window;
	Splash m_splashScreen;
	Menu m_menu;
	GamePlay m_gameplayScreen;
	Win m_winScreen;
	Lose m_loseScreen;

	bool m_exitGame;
};

#endif
