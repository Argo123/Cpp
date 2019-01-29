#pragma once

class StateMachine
{
private:
	int State = 0;
	int Tick = 0;
public:
	StateMachine();
	~StateMachine();

	void IncreaseState();
	void DecreaseState();
	int GetState();
	bool Ticks();

	StateMachine& operator=(int _tickvalue);
};

