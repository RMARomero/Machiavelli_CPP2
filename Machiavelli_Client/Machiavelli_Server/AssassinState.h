#pragma once
#include "IRoundState.h"

class AssassinState : public IRoundState
{
public:
	AssassinState();
	~AssassinState(){}

	void Handle(GameRunningState& context, GameManager& gm);

	eCharacterCard currentRole(){ return Assassin; }
};

