#pragma once
#include "IRoundState.h"

class ArchitectState : public IRoundState
{
public:
	ArchitectState();
	~ArchitectState();

	void Handle(GameRunningState& context, GameManager& gm);
	void PickBuildingCard(shared_ptr<CardDeck<BuildingCard>> cp, int amount);
	void BuildSomething();

	eCharacterCard currentRole();
	
};

