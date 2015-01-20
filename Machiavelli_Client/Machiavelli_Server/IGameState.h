#pragma once

#include <memory>

using std::shared_ptr;

class GameManager;
class IGameState
{
public:
	IGameState(){}
	virtual void Handle(GameManager& gm) = 0;
	virtual ~IGameState(){}
};

