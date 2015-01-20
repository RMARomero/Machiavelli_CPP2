#pragma once
#include "IRoundState.h"
class CharacterSelectionState :
	public IRoundState
{
public:
	CharacterSelectionState();
	void Handle(GameRunningState& context, GameManager& gm);
	virtual ~CharacterSelectionState();
	eCharacterCard currentRole() { return eCharacterCard(0); }
};

