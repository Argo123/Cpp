#include "GraphicalValues.h"



GraphicalValues::GraphicalValues()
{
}


GraphicalValues::~GraphicalValues()
{
}

void GraphicalValues::SetText(const std::string &text)
{
	TextValue.setString(text);
	TextValue.setFont(FontValue);
}

Text GraphicalValues::GetText()
{
	return TextValue;
}
