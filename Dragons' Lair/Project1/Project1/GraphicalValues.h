#pragma once

#include"Headers.h"
#include"StateMachine.h"

class GraphicalValues
{
public:
	RectangleShape Mesh;
	Text TextValue;
	Font FontValue;

	GraphicalValues();
	~GraphicalValues();
	
	virtual void SetText(const std::string &text);

	virtual Text GetText();
};

