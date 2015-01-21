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
	virtual void PickBuildingCard(shared_ptr<CardDeck<BuildingCard>> cp, int amount);
	virtual void BuildSomething();
	void RefillBuildingCardDeckIfDepleted(shared_ptr<CardManager> cm, int threshold);
};

