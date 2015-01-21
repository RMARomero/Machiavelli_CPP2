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
	void GiveDistrictCardsFromPile(shared_ptr<Player> to, shared_ptr<CardPile<DistrictCard>> pile, int amount);
};

