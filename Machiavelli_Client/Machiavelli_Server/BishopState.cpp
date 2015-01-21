#include "BishopState.h"
#include "IRoundState.h"
#include "GameRunningState.h"
#include "RoundFinishedState.h"
#include "MerchantState.h"
#include "GameManager.h"


BishopState::BishopState()
{
	printf("Bishop State\n");
}

BishopState::~BishopState()
{
}

void BishopState::Handle(GameRunningState& context, GameManager& gm)
{
	IRoundState::Handle(context, gm);
	if (m_CurrentPlayer.get() == nullptr || gm.isKilled(currentRole())) 
	{
		context.setState(unique_ptr < IRoundState > {new MerchantState});
		return;
	}
	m_CurrentPlayer->GiveGPForCards(blue);
	context.setState(unique_ptr < IRoundState > {new MerchantState});
}

eCharacterCard BishopState::currentRole() 
{
	return Bishop;
}

