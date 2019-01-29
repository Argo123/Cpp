#pragma once

#include"DragonStatus.h"

class Dragon : public DragonStatus
{
private:
	enum D_E_State{ egg, whelp, adolescent, elder };
	
	RectangleShape Mesh;
	List* First_stat;
	std::string Name;
public:
	Dragon(D_E_Type _type, std::string _name);
	~Dragon();

	void IncreaseLevel();
	void NewGen();
	std::string GetName();
	RectangleShape GetMesh();
	D_E_Type GetType();
	List* Head;
};

