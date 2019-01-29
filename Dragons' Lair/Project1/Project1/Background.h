#pragma once

#include"GraphicalValues.h"

class Background : virtual public GraphicalValues
{
private:
	Texture Tex;
public:
	Background(int type, int width, int height);
	~Background();

	RectangleShape GetMesh();
};

