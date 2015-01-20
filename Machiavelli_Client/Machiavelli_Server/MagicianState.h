#pragma once
#include "IRoundState.h"
class MagicianState :
	public IRoundState
{

public:
	MagicianState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole();
	~MagicianState();
};

