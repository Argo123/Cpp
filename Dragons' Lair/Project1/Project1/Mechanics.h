#pragma once

#include"Headers.h"
#include"CustomButton.h"
#include"Dragon.h"

#define FEED_VALUE 100
#define PLAY_VALUE 100
#define SOOTHE_VALUE -50

void Buttons_Menu_Handle(CustomButton *ar_b, bool &wasSet, bool &wasMenuDrawn);

void Buttons_Handle(CustomButton *ar_b, bool &wereButtonsSet, Dragon *currentDragon);

void Buttons_Menu_Events(Window* window, CustomButton *ar_b, Dragon* &currentDragon);

void Buttons_Events(Window* window, CustomButton *ar_b, Dragon* currentDragon);

void Event_Ticks(CustomButton *ar_b, Dragon *currentDragon);

std::string Convert(int value);

void Save(Dragon *currentDragon);

bool Load(Dragon *&currentDragon);