#pragma once

#include "Counter.h"

class List
{
private:
	List* Next = nullptr;
public:
	Texture* Text;
	int StateValue;

	List();
	~List();

	void SetNext(List* _next);
	List* GetNext();
};

