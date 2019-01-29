#pragma once

#include "Background.h"

#define TICKS 3

class CustomButton : virtual private GraphicalValues
{
private:
	enum B_E_State{ free, pressed };

	Texture Ar_t[2];
public:
	StateMachine State;
	
	CustomButton();
	~CustomButton();

	void SetFreeTexture(const std::string& path, int x, int y);
	void SetPressedTexture(const std::string& path, int x, int y);
	void SetPosition(int x, int y);
	void SetText(const std::string &text);

	CustomButton& operator()(int x, int y);

	RectangleShape GetMesh();
	Text GetText();

	void Pressed();
	void ChangeState();
};
