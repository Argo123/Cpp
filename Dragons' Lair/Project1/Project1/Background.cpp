#include "Background.h"



Background::Background(int type, int width, int height)
{
	std::string path = "Textures/Background/Background_.png";
	std::string in;

	Mesh = RectangleShape(Vector2f(width, height));
	Mesh.setPosition(Vector2f(0, 0));

	in = (char)type + 48; //Parsowanie stringa pod odczyt tekstury tla odpowiadajacej typowi smoka
	path.insert(path.length() - 4, in);

	Tex.loadFromFile(path, IntRect(0, 0, width, height));

	Mesh.setTexture(&Tex);
}



Background::~Background()
{
}

RectangleShape Background::GetMesh()
{
	return Mesh;
}
