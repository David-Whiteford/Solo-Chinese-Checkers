#pragma once
#ifndef GLOBALS
#define GLOBALS

enum class  GameMode
{
	Splash,
	Menu,
	Gameplay,
	Lose,
	Win,
};

enum class Difficulty
{
	Easy,
	Medium,
	Hard
};


const static int SCREEN_WIDTH = 620;
const static int SCREEN_HEIGHT = 440;
const static int MS_PER_UPDATE = 10;

const static float PI = 3.14159265359;
float const DEG_TO_RAD = PI / 180.0f;
float const RAD_TO_DEG = 180.0f / PI;

#endif