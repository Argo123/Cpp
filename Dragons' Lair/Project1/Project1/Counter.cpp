#include "Counter.h"
#include<sstream>

Counter::Counter()
{
	FontValue.loadFromFile("Textures/Endor.ttf");
	TextValue.setFillColor(Color::Black);
}

Counter::~Counter()
{
}

std::string Convert(int value)
{
	std::stringstream s_temp;
	s_temp << value;
	std::string str = s_temp.str();

	return str;
}

void Counter::SetText(int value)
{
	std::string str = Convert(value);
	
	TextValue.setString(str);
	TextValue.setFont(FontValue);

	TextValue_MAX.setFont(FontValue);
}

void Counter::SetPosition(int x, int y)
{
	TextValue.setPosition(Vector2f(x, y));
	TextValue_MAX.setPosition(Vector2f(x + 75, y));
}

void Counter::SetMaxValue(int _maxValue)
{
	MaxValue = _maxValue;

	std::string str = Convert(_maxValue);

	TextValue_MAX.setString(str);
	TextValue_MAX.setFillColor(Color::Black);

	CurrentValue = 0;
}

int Counter::GetMaxValue()
{
	return MaxValue;
}

int Counter::GetCurrentValue()
{
	return CurrentValue;
}

Text Counter::GetText()
{
	return TextValue;
}

Text Counter::GetText_MAX()
{
	return TextValue_MAX;
}

bool Counter::ChangeCurrentValue(int value)
{
	CurrentValue += value;

	if (CurrentValue >= MaxValue) return true;
	else return false;
}

void Counter::ChangeCurrentValueTo(int value)
{
	CurrentValue = value;
}

void Counter::ChangeColor(Color color)
{
	TextValue.setFillColor(color);
	TextValue_MAX.setFillColor(color);
}

Counter& Counter::operator+(int value)
{
	CurrentValue += value;

	return *this;
}