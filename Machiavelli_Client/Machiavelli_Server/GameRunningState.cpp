#include "GameRunningState.h"
#include "GameManager.h"
#include "IRoundState.h"
#include "InitRoundState.h"

GameRunningState::GameRunningState()
{
	m_CurrentRoundState = shared_ptr<IRoundState> {new InitRoundState};
	//m_CurrentRound = new InitRoundState();
}

void GameRunningState::Handle(GameManager& gm)
{
	gm.GetPlayerList()->SendAll("We are ready to begin. Goodluck and have fun!\n");

	while (true)
	{
		m_CurrentRoundState->Handle(*this, gm);
	}
}

void GameRunningState::setState(shared_ptr<IRoundState> roundState)
{
	m_CurrentRoundState = roundState;
}