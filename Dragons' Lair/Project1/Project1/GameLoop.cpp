#include "GameLoop.h"
#include "Mechanics.h"
#include<iostream>

GameLoop::GameLoop(uint32_t windowWidth, uint32_t windowHeight, std::string windowName, Color windowDefaultColor)
	: WindowDefaultColor(windowDefaultColor)
{
	Window = new RenderWindow(VideoMode(windowWidth, windowHeight), windowName);
}


GameLoop::~GameLoop()
{
	delete Window;
	delete CurrentDragon;

	for (int i = 0; i < NUMBER_OF_BACKGROUNDS; ++i)
		delete Bg[i];
}

void GameLoop::Run()
{
	float totalTimePassed = 0.0f;	
	float deltaTime = 0.0f;
	float timeBeforeUpdate = 0.0f;
	float previousTotalTimePassed = 0.0f;  

	bool wasMenuDrawn = false;
	bool wasSet = false;
	bool wereButtonsSet = false;
	Clock clock;

	while (Window->isOpen())
	{
		totalTimePassed = (clock.getElapsedTime()).asSeconds(); //Wymuszanie statycznej wartoœci FPS
		deltaTime = totalTimePassed - previousTotalTimePassed;
		previousTotalTimePassed = totalTimePassed;

		timeBeforeUpdate += deltaTime;

		if (timeBeforeUpdate >= TIME_UNTIL_UPDATE)
		{
			Window->clear(WindowDefaultColor);

			if (!wasMenuDrawn) //Rysowanie Menu
			{
				DrawMenu(wasSet, wasMenuDrawn);

				Window->display();

				timeBeforeUpdate = 0;

				continue;
			}

			DrawMain(wereButtonsSet); //Rysowanie glownego okna gry

			Window->display();

			timeBeforeUpdate = 0;
		}
	}
}

void GameLoop::DrawMenu(bool &wasSet, bool &wasMenuDrawn)
{
	Buttons_Menu_Handle(Ar_b, wasSet, wasMenuDrawn);

	for (int i = 0; i < 4; ++i)
			Window->draw(Ar_b[i].GetMesh()); //Rysowanie obiektow

	Buttons_Menu_Events(Window, Ar_b, CurrentDragon);

	if (wasMenuDrawn) //Przywracanie guzikow do ich regularnych form
	{
		for (int i = 0; i < 3; ++i)
		{
			Ar_b[i] = CustomButton();
			Ar_b[i].Pressed();
		}

		Bg[2] = new Background(CurrentDragon->GetType(), 600, 428);
		Bg[1] = new Background(4, 620, 448);
		Bg[0] = new Background(5, 840, 528);

		for (int i = 0; i < NUMBER_OF_BACKGROUNDS; ++i)
			ar_m[i] = Bg[i]->GetMesh();
	}
}

void GameLoop::DrawMain(bool &wereButtonsSet)
{

	ar_m[NUMBER_OF_MESHES - NUMBER_OF_BACKGROUNDS - 1] = CurrentDragon->GetMesh(); //Sczytywanie obiektu smoka

	if(!wereButtonsSet) Buttons_Handle(Ar_b, wereButtonsSet, CurrentDragon); //Ustawianie guzikow

	CurrentDragon->Ar_c[DragonStatus::Fed].SetText(CurrentDragon->Ar_c[DragonStatus::Fed].GetCurrentValue()); //Sczytywanie wartosci tekstowych smoka
	CurrentDragon->Ar_c[DragonStatus::Played].SetText(CurrentDragon->Ar_c[DragonStatus::Played].GetCurrentValue());
	CurrentDragon->Ar_c[DragonStatus::Angered].SetText(CurrentDragon->Ar_c[DragonStatus::Angered].GetCurrentValue());

	String = "Generation: "; //Ustawianie napisu o pokoleniu smoka

	Generation.SetText(0);
	Generation.TextValue.setString(String + Convert(CurrentDragon->Generation.GetState()));
	Generation.SetPosition(50, 460);
	Generation.TextValue.setFillColor(Color::Black);

	Event_Ticks(Ar_b, CurrentDragon); //Spadek tików w guzikach

	for (int i = NUMBER_OF_BACKGROUNDS + 1; i < NUMBER_OF_MESHES; ++i) 
		ar_m[i] = Ar_b[i-NUMBER_OF_BACKGROUNDS - 1].GetMesh(); //Sczytywanie obiektów buzikow

	for (int i = 0; i < NUMBER_OF_TEXTS - 6; ++i) 
		ar_txt[i] = Ar_b[i].GetText(); //Sczytywanie obiektow tekstowych guzikow

	for (int i = 3; i < NUMBER_OF_TEXTS - 3; ++i) //Sczytywanie obiektow tekstowych licznikow
	{
		ar_txt[i] = CurrentDragon->Ar_c[i - 3].GetText();
		ar_txt[i + 3] = CurrentDragon->Ar_c[i - 3].GetText_MAX();
	}

	for (int i = 0; i < NUMBER_OF_MESHES; ++i) //Rysowanie obiektow
		Window->draw(ar_m[i]); 

	for (int i = 0; i < NUMBER_OF_TEXTS; ++i) //Rysowanie tekstu
		Window->draw(ar_txt[i]);

	Window->draw(Generation.GetText());

	Buttons_Events(Window, Ar_b, CurrentDragon); //Obsluga wydarzen
}
