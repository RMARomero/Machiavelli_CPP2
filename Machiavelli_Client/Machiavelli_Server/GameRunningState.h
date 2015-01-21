#pragma once
#include "IGameState.h"
#include "IRoundState.h"

class GameRunningState : public IGameState
{
public:
	GameRunningState();
	virtual ~GameRunningState(){}

	void Handle(GameManager& gm);
	void setState(shared_ptr<IRoundState> roundState);
private:
	shared_ptr<IRoundState> m_CurrentRound;
};

