#pragma once

#include"CustomButton.h"

class Counter : virtual public GraphicalValues
{
private:
	int MaxValue;
	Text TextValue_MAX;
public:
	int CurrentValue;

	Counter();

	~Counter();

	void SetText(int value);
	void SetPosition(int x, int y);
	void SetMaxValue(int _maxValue);

	int GetMaxValue();
	int GetCurrentValue();
	Text GetText();
	Text GetText_MAX();

	bool ChangeCurrentValue(int value);
	void ChangeCurrentValueTo(int value);
	void ChangeColor(Color color);

	Counter& operator+(int value);
};

std::string Convert(int value);
