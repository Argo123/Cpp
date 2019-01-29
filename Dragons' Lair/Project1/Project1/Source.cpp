#include<iostream>
#include"GameLoop.h"

#define DEFAULT_WIDTH 840
#define DEFAULT_HEIGHT 528

using namespace std;

int main()
{
	GameLoop* instance = new GameLoop(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Dragon's Lair", sf::Color::Black);

	instance->Run();

	delete instance;

	return 0;
}