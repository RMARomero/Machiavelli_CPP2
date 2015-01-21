#pragma once
#include "IRoundState.h"

class CharacterSelectionState :	public IRoundState
{
public:
	CharacterSelectionState();
	virtual ~CharacterSelectionState();

	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole() { return eCharacterCard(0); }
};

