#pragma once
#include "IRoundState.h"

class ArchitectState : public IRoundState
{
public:
	ArchitectState();
	~ArchitectState();

	void Handle(GameRunningState& context, GameManager& gm);
	void PickDistrictCard(shared_ptr<CardPile<DistrictCard>> cp, int amount);
	void BuildSomething();

	eCharacterCard currentRole();
	
};

