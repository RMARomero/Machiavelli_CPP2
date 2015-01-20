#pragma once
#include "IRoundState.h"
class ThiefState :
	public IRoundState
{
public:
	ThiefState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole();
	virtual ~ThiefState();
};

