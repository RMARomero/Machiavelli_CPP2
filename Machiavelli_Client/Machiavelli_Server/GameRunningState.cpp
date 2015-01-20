#include "GameRunningState.h"
#include "GameManager.h"
#include "IRoundState.h"
#include "InitRoundState.h"

GameRunningState::GameRunningState()
{
	m_CurrentRound = shared_ptr < IRoundState > {new InitRoundState};
}

void GameRunningState::Handle(GameManager& gm)
{
	gm.GetPlayerList()->SendAll("Everyone seems ready! Happy Citadels Game, and may the odds be ever in your favor!");

	while (true)
	{
		m_CurrentRound->Handle(*this, gm);
	}
}

void GameRunningState::setState(shared_ptr<IRoundState> roundState)
{
	m_CurrentRound = roundState;
}