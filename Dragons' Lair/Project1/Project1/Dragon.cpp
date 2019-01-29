#include "Dragon.h"
#include<iostream>

Dragon::Dragon(D_E_Type _type, std::string _name) 
	 :Name(_name)
{
	std::string path = "Textures/Dragons/Dragon_x_.png";
	std::string in;

	Type = _type;

	Head = new List;

	First_stat = Head;
	List* Next;

	Mesh = RectangleShape(Vector2f(60, 80));
	
	in = (char)Type + 48;
	path.insert(path.length()-4, in);

	for (char i = 0; i < 4; ++i) //Parsowanie stringa, aby wczytal odpowiednie tekstury
	{
		path.erase(24, 1);

		in = (char)i + 48;

		path.insert(24, in);

		Next = new List;

		Head->StateValue = i;
		Head->Text->loadFromFile(path, IntRect(0, 0, 600, 428)); //Wczytywanie tekstur
		Head->SetNext(Next);
		Head = Next;
	}

	Mesh.setTexture(First_stat->Text);
	Mesh.setPosition(Vector2f(280, 328));

	Head = First_stat;

	SetValues();
}


Dragon::~Dragon()
{
	while (Head->GetNext() != nullptr)
	{
		First_stat = Head->GetNext();

		delete Head;

		Head = First_stat;
	}

	delete Head;
}

std::string Dragon::GetName()
{
	return Name;
}

RectangleShape Dragon::GetMesh()
{
	return Mesh;
}

Dragon::D_E_Type Dragon::GetType()
{
	return Type;
}

void Dragon::NewGen() //Obsluga nowego pokolenia
{
	while(Level.GetState() != 0) Level.DecreaseState();

	Generation.IncreaseState();

	if (Generation.GetState() >= 5) //Wczytywanie zlotych tekstur po osiagnieciu 5 pokolenia
	{
		std::string path = "Textures/Dragons/Dragon_x__GOLDEN.png";
		std::string in;
		in = (char)Type + 48;

		Head = First_stat;

		List* Next; 

		path.insert(path.length() - 11, in);

		for (char i = 0; i < 4; ++i) //Parsowanie stringa, aby wczytal odpowiednie tekstury
		{
			path.erase(24, 1);

			in = (char)i + 48;

			path.insert(24, in);

			Next = Head->GetNext();

			Head->StateValue = i;
			Head->Text->loadFromFile(path, IntRect(0, 0, 600, 428)); //Wczytywanie
			Head->SetNext(Next);
			Head = Next;
		}
		Head = First_stat;
	}

	Mesh.setTexture(Head->Text);
	Mesh.setPosition(Vector2f(280, 328));

	SetValues();
}

void Dragon::IncreaseLevel()
{
	Level.IncreaseState();
	Head = Head->GetNext();

	if (Level.GetState() > elder) //Nowa generacja
	{
		Head = First_stat;
		NewGen();
	}

	switch (Level.GetState()) //Dostosowywanie ekranu w zaleznosci od rozmiaru smoka
	{
	case whelp:
		Mesh = RectangleShape(Vector2f(120, 120));
		Mesh.setPosition(Vector2f(240, 308));
		Mesh.setTexture(Head->Text);
		break;
	case adolescent:
		Mesh = RectangleShape(Vector2f(350, 300));
		Mesh.setPosition(Vector2f(125, 128));
		Mesh.setTexture(Head->Text);
		break;
	case elder:
		Mesh = RectangleShape(Vector2f(600, 428));
		Mesh.setPosition(Vector2f(0, 0));
		Mesh.setTexture(Head->Text);
		break;
	}

	SetValues();

	Ar_grow[Fed]= 0; //Resetowanie tikow
	Ar_grow[Played]= 0;
}