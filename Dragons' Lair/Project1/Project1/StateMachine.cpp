#include "StateMachine.h"
#include<iostream>


StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::IncreaseState()
{
	State++;
}

void StateMachine::DecreaseState()
{
	 State--;
}

int StateMachine::GetState()
{
	return State;
}

bool StateMachine::Ticks()
{
	--Tick;

	if (Tick < 0)
	{
		DecreaseState();
		return true;
	}

	return false;
}

StateMachine& StateMachine::operator=(int _tickvalue) //Operator ustawiajacy tiki
{
	Tick = _tickvalue;
	return *this;
}
