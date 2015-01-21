#include "MerchantState.h"
#include "GameRunningState.h"
#include "ArchitectState.h"
#include "GameManager.h"

MerchantState::MerchantState()
{
	printf("Merchant State\n");
}

void MerchantState::Handle(GameRunningState& context, GameManager& gm)
{
	IRoundState::Handle(context, gm);

	if (m_CurrentPlayer.get() == nullptr || gm.isKilled(currentRole())) 
	{
		context.setState(unique_ptr<IRoundState> {new ArchitectState});
		return;
	}

	m_CurrentPlayer->GiveGoldPieces(1);
	m_CurrentPlayer->GiveGPForCards(green);

	context.setState(unique_ptr<IRoundState> {new ArchitectState});
}
