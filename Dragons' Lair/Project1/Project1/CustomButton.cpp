#include "CustomButton.h"

CustomButton::CustomButton()
{
	Mesh = RectangleShape(Vector2f(200, 100));

	Ar_t[free].loadFromFile("Textures/Buttons/button.png", IntRect(0, 0, 200, 100));
	Ar_t[pressed].loadFromFile("Textures/Buttons/button_pressed.png", IntRect(0, 0, 200, 100));

	Mesh.setTexture(&Ar_t[free]);

	FontValue.loadFromFile("Textures/Endor.ttf");

	TextValue.setFillColor(Color::Black);
}


CustomButton::~CustomButton()
{
}

void CustomButton::SetFreeTexture(const std::string& path, int x, int y)
{
	Ar_t[free].loadFromFile(path, IntRect(0, 0, x, y)); //Ustawianie tekstury guzika 
	Mesh.setTexture(&Ar_t[free]);
}

void CustomButton::SetPressedTexture(const std::string& path, int x, int y)
{
	Ar_t[pressed].loadFromFile(path, IntRect(0, 0, x, y)); //Ustawianie tekstury guzika wcisnietego
}

void CustomButton::SetPosition(int x, int y)
{
	Mesh.setPosition(Vector2f(x, y)); 
	TextValue.setPosition(Vector2f(x + 70, y + 32));
}

void CustomButton::SetText(const std::string &text)
{
	TextValue.setString(text);
	TextValue.setFont(FontValue);
}

RectangleShape CustomButton::GetMesh()
{
	return Mesh;
}

Text CustomButton::GetText()
{
	return TextValue;
}

void CustomButton::Pressed()
{
	State.IncreaseState(); //Wciskanie guzika
	State = TICKS;
	ChangeState();
}

void CustomButton::ChangeState()
{
	switch (State.GetState()) //Ustawianie odpowiedniej tekstury w zaleznosci od stanu guzika
	{
	case free:
		Mesh.setTexture(&Ar_t[free]);
		break;
	case pressed:
		Mesh.setTexture(&Ar_t[pressed]);
		break;
	}
}

CustomButton& CustomButton::operator()(int x, int y)
{
	Mesh = RectangleShape(Vector2f(x, y));

	return *this;
}