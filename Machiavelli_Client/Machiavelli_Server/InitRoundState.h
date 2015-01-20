#pragma once
#include "IRoundState.h"
class InitRoundState :
	public IRoundState
{
private:
	void GiveDistrictCardsFromPile(shared_ptr<Player> to, shared_ptr<CardPile<DistrictCard>> pile, int amount);
public:
	InitRoundState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole() { return eCharacterCard(0); }
};

