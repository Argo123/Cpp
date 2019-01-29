#include "DragonStatus.h"



DragonStatus::DragonStatus()
{
}


DragonStatus::~DragonStatus()
{
}

void DragonStatus::SetValues() //Ustawianie personalnych wartosci dla kazdego typu smoka
{
	switch (Type)
	{
	case molten:
		Ar_c[Fed].SetMaxValue((500 * (1 + Level.GetState()) + 250 * (Level.GetState()*Type)) * (0.5 * Generation.GetState() + 1));
		Ar_c[Played].SetMaxValue((400 * (1 + Level.GetState()) + 200 * (Level.GetState()*Type)) * (0.5 * Generation.GetState() + 1));
		Ar_c[Angered].SetMaxValue((200 * (1 + Level.GetState())) + 1000/(20*(Generation.GetState()+1)));

		break;
	case weather:
		Ar_c[Fed].SetMaxValue((550 * (1 + Level.GetState()) + 300 * (Level.GetState()*Type)) * (0.5 * Generation.GetState() + 1));
		Ar_c[Played].SetMaxValue((450 * (1 + Level.GetState()) + 200 * (Level.GetState()*Type)) * (0.65 * Generation.GetState() + 1));
		Ar_c[Angered].SetMaxValue((150 * (1 + Level.GetState())) + 800 / (20 * (Generation.GetState() + 1)));

		break;
	case frost:
		Ar_c[Fed].SetMaxValue((600 * (1 + Level.GetState()) + 350 * (Level.GetState()*Type)) * (0.5 * Generation.GetState() + 1));
		Ar_c[Played].SetMaxValue((500 * (1 + Level.GetState()) + 250 * (Level.GetState()*Type)) * (0.65 * Generation.GetState() + 1));
		Ar_c[Angered].SetMaxValue((150 * (1 + Level.GetState())) + 800 / (20 * (Generation.GetState() + 1)));

		break;
	}

	Growth[Fed] = Growth[Played] = Growth[Angered] = false;
}

bool DragonStatus::AbleToGrow()
{
	if (Growth[Fed] && Growth[Played] && !Growth[Angered]) return true; //Sprawdzanie warunku czy smok moze urosnac
	else return false;
}