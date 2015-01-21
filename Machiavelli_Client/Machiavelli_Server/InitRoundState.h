#pragma once
#include "IRoundState.h"

class InitRoundState :	public IRoundState
{
public:
	InitRoundState();
	virtual ~InitRoundState() {};

	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole() { return eCharacterCard(0); }
private:
	void GiveBuildingCardsFromDeck(shared_ptr<Player> to, shared_ptr<CardDeck<BuildingCard>> pile, int amount);
};

