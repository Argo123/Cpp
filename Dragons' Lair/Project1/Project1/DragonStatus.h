#pragma once

#include"List.h"

class DragonStatus
{
private:
public:
	enum D_E_Type { molten = 1, weather, frost };
	enum D_E_Values { Fed, Played, Angered };

	bool Growth[3] = { false };
	StateMachine Ar_grow[3];

	D_E_Type Type;
	StateMachine Level;
	StateMachine Generation;
	Counter Ar_c[3];

	DragonStatus();
	~DragonStatus();

	void SetValues();
	bool AbleToGrow();
};

