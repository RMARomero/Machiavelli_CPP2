#pragma once
#include "IGameState.h"
#include "IRoundState.h"
class GameRunningState :
	public IGameState
{
private:
	shared_ptr<IRoundState> m_CurrentRound;
public:
	GameRunningState();
	void Handle(GameManager& gm);
	virtual ~GameRunningState();
	void setState(shared_ptr<IRoundState> roundState);
};

