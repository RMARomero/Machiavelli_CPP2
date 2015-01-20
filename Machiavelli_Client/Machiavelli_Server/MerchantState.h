#pragma once
#include "IRoundState.h"
class MerchantState :
	public IRoundState
{
public:
	MerchantState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole();
	~MerchantState();
};

