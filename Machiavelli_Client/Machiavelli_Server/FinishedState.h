#pragma once
#include "IGameState.h"
#include <map>
class Player;
using std::map;

class FinishedState :
	public IGameState
{
private:
	bool HasBuildingsOf5Colours(shared_ptr<Player> player);
	shared_ptr<Player> GetWinningPlayer(map<shared_ptr<Player>, int> scoreboard);
public:
	FinishedState();
	void Handle(GameManager& gm);
	~FinishedState();
};

