#include "KingState.h"
#include "GameRunningState.h"
#include "BishopState.h"
#include "GameManager.h"

KingState::KingState()
{
	printf("King State\n");
}

void KingState::Handle(GameRunningState& context, GameManager& gm)
{
	IRoundState::Handle(context, gm);

	if (m_CurrentPlayer.get() == nullptr || gm.isKilled(currentRole())) 
	{
		context.setState(unique_ptr<IRoundState> {new BishopState});
		return;
	}
	m_CurrentPlayer->GiveGPForCards(yellow);

	gm.GetPlayerList()->MoveToFront(m_CurrentPlayer);
	context.setState(unique_ptr<IRoundState> {new BishopState});
}

