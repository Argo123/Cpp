#include"Mechanics.h"
#include <sstream>
#include <fstream>
void Dragon_Value_Handler(Dragon* currentDragon, int type, int value)
{
	if (currentDragon->Ar_c[type].GetCurrentValue() <= currentDragon->Ar_c[type].GetMaxValue())
		if (currentDragon->Ar_c[type].ChangeCurrentValue(value)) //Ustawianie maksymalnej wartosci na zielono
		{
			currentDragon->Ar_grow[type].IncreaseState();
			currentDragon->Ar_grow[type]= 90;
			currentDragon->Growth[type] = true;

			if (type == DragonStatus::Angered) //Zerowanie licznikow przy osiagnieciu maksymalnego zdenerwowania
			{
				currentDragon->Ar_c[type].ChangeColor(Color::Red);
				currentDragon->Ar_c[DragonStatus::Angered].ChangeCurrentValueTo(0);
				currentDragon->Ar_c[DragonStatus::Played].ChangeCurrentValueTo(0);
				currentDragon->Ar_c[DragonStatus::Fed].ChangeCurrentValueTo(0);
			}
			else 
				currentDragon->Ar_c[type].ChangeColor(Color::Green);
		}
}

void Buttons_Handle(CustomButton *ar_b, bool &wereButtonsSet, Dragon *currentDragon)
{
	ar_b[0].SetPosition(625, 35); //Ustawianie guzikow na odpowiednim miejscu
	ar_b[0].SetText("Feed");

	ar_b[1].SetPosition(625, 175);
	ar_b[1].SetText("Play");

	ar_b[2].SetPosition(625, 310);
	ar_b[2].SetText("Soothe");

	currentDragon->Ar_c[DragonStatus::Fed].SetPosition(625, 0);

	currentDragon->Ar_c[DragonStatus::Played].SetPosition(625, 135);

	currentDragon->Ar_c[DragonStatus::Angered].SetPosition(625, 275);

	wereButtonsSet = true;
}

void Buttons_Menu_Handle(CustomButton *ar_b, bool &wasSet, bool &wasMenuDrawn)
{
	for (int i = 0; i < 4; ++i)
		if (ar_b[i].State.GetState() != 0) 
			if (ar_b[i].State.Ticks())
				wasMenuDrawn = true; //Wymuszanie opoznienia, aby pokazac animacje naciskania przycisku


	if (!wasSet) //Ustawianie nieregularnych wartosci guzikow
	{
		int dimX = 200;
		int dimY = 300;

		ar_b[0](dimX, dimY);
		ar_b[0].SetFreeTexture("Textures/Dragons/Dragon_0_1.png", dimX, dimY);
		ar_b[0].SetPressedTexture("Textures/Buttons/Dragon_1.png", dimX, dimY);
		ar_b[0].SetPosition(50, 50);

		ar_b[1](dimX, dimY);
		ar_b[1].SetFreeTexture("Textures/Dragons/Dragon_0_2.png", dimX, dimY);
		ar_b[1].SetPressedTexture("Textures/Buttons/Dragon_2.png", dimX, dimY);
		ar_b[1].SetPosition(300, 50);

		ar_b[2](dimX, dimY);
		ar_b[2].SetFreeTexture("Textures/Dragons/Dragon_0_3.png", dimX, dimY);
		ar_b[2].SetPressedTexture("Textures/Buttons/Dragon_3.png", dimX, dimY);
		ar_b[2].SetPosition(550, 50);

		ar_b[3](200, 100);
		ar_b[3].SetFreeTexture("Textures/Buttons/load_button_f.png", 200, 100);
		ar_b[3].SetPressedTexture("Textures/Buttons/load_button_p.png", 200, 100);
		ar_b[3].SetPosition(300, 400);

		wasSet = true;
	}
}

void EventCheck(Window* window, CustomButton *ar_b, Dragon* &currentDragon, DragonStatus::D_E_Type type, Event event)
{
	Vector2i mousePos = Mouse::getPosition(*window);
	Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if ((event.type == Event::MouseButtonPressed) && ar_b[type-1].GetMesh().getGlobalBounds().contains(mousePosF)) //Sprawdzanie czy guzik zostal wcisniety
	{
		ar_b[type - 1].Pressed();

		if (type == 4)
		{
			if(!Load(currentDragon)) window->close();
			return;
		}

		currentDragon = new Dragon(type, "Kasia");
	}
}

void Buttons_Menu_Events(Window* window, CustomButton *ar_b, Dragon* &currentDragon)
{
	Event event;

	while (window->pollEvent(event))
	{
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)) //Escape button
			window->close();

		EventCheck(window, ar_b, currentDragon, DragonStatus::D_E_Type::molten, event); //Sprawdzanie nacisniec poszczegolnych guzikow
		EventCheck(window, ar_b, currentDragon, DragonStatus::D_E_Type::weather, event);
		EventCheck(window, ar_b, currentDragon, DragonStatus::D_E_Type::frost, event);
		EventCheck(window, ar_b, currentDragon, (DragonStatus::D_E_Type)4, event); //Sprawdzanie wcisniecia przycisku "Load"
	}
}

void Buttons_Events(Window* window, CustomButton *ar_b, Dragon* currentDragon)
{
	Event event;
	
	while (window->pollEvent(event))
	{
		Vector2i mousePos = Mouse::getPosition(*window);
		Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)) //Obsluga klawisza Escape
		{
			window->close();
			Save(currentDragon); //Zapis smoka
		}

		if ((event.type == Event::MouseButtonPressed) && ar_b[0].GetMesh().getGlobalBounds().contains(mousePosF)) //Karmienie
		{
			ar_b[0].Pressed();
			Dragon_Value_Handler(currentDragon, DragonStatus::Fed, FEED_VALUE);
		}

		if ((event.type == Event::MouseButtonPressed) && ar_b[1].GetMesh().getGlobalBounds().contains(mousePosF)) //Bawienie
		{
			ar_b[1].Pressed();
			Dragon_Value_Handler(currentDragon, DragonStatus::Played, PLAY_VALUE);
		}

		if ((event.type == Event::MouseButtonPressed) && ar_b[2].GetMesh().getGlobalBounds().contains(mousePosF)) //Opanowanie
		{
			ar_b[2].Pressed();
			if (currentDragon->Ar_c[DragonStatus::Angered].GetCurrentValue() > 50) 
				Dragon_Value_Handler(currentDragon, DragonStatus::Angered, SOOTHE_VALUE);
		}
	}

	if (currentDragon->AbleToGrow()) //Sprawdzanie warunku czy moze urosnac
		currentDragon->IncreaseLevel();

	if (currentDragon->Ar_c[DragonStatus::Fed].GetCurrentValue() > 0)
	{
		currentDragon->Ar_c[DragonStatus::Fed].ChangeCurrentValue(-1); //Spadek wartosci nakarmienia
		Dragon_Value_Handler(currentDragon, DragonStatus::Angered, 1);
	}

	if (currentDragon->Ar_c[DragonStatus::Played].GetCurrentValue() > 0)
	{
		currentDragon->Ar_c[DragonStatus::Played].ChangeCurrentValue(-1); //Spadek wartosci wybawienia
		Dragon_Value_Handler(currentDragon, DragonStatus::Angered, 1);
	}
}

void Event_Ticks(CustomButton *ar_b, Dragon *currentDragon)
{
	//GUZIKI
	for (int i = 0; i < 3; ++i)
		if (ar_b[i].State.GetState() != 0)
			if (ar_b[i].State.Ticks())
				ar_b[i].ChangeState(); //Wymuszanie opoznienia, aby pokazac animacje naciskania przycisku
	//WARTOSCI
	for (int i = 0; i < 3; ++i)
		if (currentDragon->Ar_grow[i].GetState() != 0)
			if (currentDragon->Ar_grow[i].Ticks())
			{
				currentDragon->Growth[i] = false;
				currentDragon->Ar_c[i].ChangeColor(Color::Black);
			}
}

void Save(Dragon *currentDragon)
{
	using namespace std; //Zapisywanie smoka

    ofstream plz("Dragon.sav");

	plz << currentDragon->GetType() << endl
		<< currentDragon->Generation.GetState() << endl
		<< currentDragon->Level.GetState() << endl;

	plz.close();
}

bool Load(Dragon *&currentDragon)
{
	using namespace std; //Wczytywanie smoka

	ifstream plo("Dragon.sav");

	int buffor_Value;

	if (plo.good())
	{
		plo >> buffor_Value;
		currentDragon = new Dragon((DragonStatus::D_E_Type)buffor_Value, "Karolina");

		plo >> buffor_Value;
		for (int i = 0; i < buffor_Value; ++i)
			currentDragon->NewGen();

		plo >> buffor_Value;
		for (int i = 0; i < buffor_Value; ++i)
			currentDragon->IncreaseLevel();
		
		plo.close();
		return true;
	} 
	else
	{
		plo.close();
		return false;
	}
}