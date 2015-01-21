#pragma once

#include <memory>
#include "CharacterCard.h"
#include "Player.h"

using std::shared_ptr;
using std::unique_ptr;

class GameManager;
class CardManager;
class IGameState;
class GameRunningState;
class IRoundState
{
public:
	IRoundState(){}
	virtual ~IRoundState(){}

	virtual void Handle(GameRunningState& context, GameManager& gm);
	virtual eCharacterCard currentRole() = 0;

protected:
	shared_ptr<Player> m_CurrentPlayer;
	virtual void PickDistrictCard(shared_ptr<CardPile<DistrictCard>> cp, int amount);
	virtual void BuildSomething();
	void RefillDistrictCardPileIfDepleted(shared_ptr<CardManager> cm, int threshold);
};

