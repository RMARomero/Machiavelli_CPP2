#pragma once
#include "IRoundState.h"

class ThiefState : public IRoundState
{
public:
	ThiefState();
	virtual ~ThiefState(){}

	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole() { return Thief; }
};

