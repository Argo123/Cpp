#pragma once

#include"Dragon.h"

#define NUMBER_OF_MESHES 7
#define NUMBER_OF_TEXTS 9
#define NUMBER_OF_BACKGROUNDS 3

class GameLoop
{
public:
	const float TARGET_FPS = 30;
	const float TIME_UNTIL_UPDATE = 1/TARGET_FPS;

	CustomButton Ar_b[4];
	StateMachine States;
	Color WindowDefaultColor;
	RenderWindow* Window;
	Dragon* CurrentDragon;
	Background* Bg[NUMBER_OF_BACKGROUNDS];
	std::string String;

	RectangleShape ar_m[NUMBER_OF_MESHES]; //Array of meshes for easier drawing
	Text ar_txt[NUMBER_OF_TEXTS]; //Array of text for easier drawing
	Counter Generation;

	GameLoop(uint32_t windowWidth, uint32_t windowHeight, std::string windowName, Color windowDefaultColor);
	~GameLoop();

	void Run();
	void DrawMenu(bool &wasSet, bool &wasMenuDrawn);
	void DrawMain(bool &wereButtonsSet);
};

