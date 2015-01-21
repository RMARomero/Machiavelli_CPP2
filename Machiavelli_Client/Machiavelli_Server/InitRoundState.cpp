#include "InitRoundState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "CharacterSelectionState.h"

#define STARTING_GOLD_AMMOUNT 2
#define STARTING_HAND_AMMOUNT 4

InitRoundState::InitRoundState()
{
	printf("InitRound State\n");
}

void InitRoundState::Handle(GameRunningState& context, GameManager& gm)
{
	gm.GetCardManager()->GetBuildingCardDeck()->shuffle();

	for (int i = 0; i < gm.GetPlayerList()->Size(); i++) 
	{
		shared_ptr<Player> player = gm.GetPlayerList()->GetPlayerAt(i);

		player->GiveGoldPieces(STARTING_GOLD_AMMOUNT);

		GiveBuildingCardsFromDeck(player, gm.GetCardManager()->GetBuildingCardDeck(), STARTING_HAND_AMMOUNT);
	}

	context.setState(shared_ptr <IRoundState> {new CharacterSelectionState});
}

void InitRoundState::GiveBuildingCardsFromDeck(shared_ptr<Player> toPlayer, shared_ptr<CardDeck<BuildingCard>> pile, int amount)
{
	if (pile->size() < amount)
	{
		printf("Card stock is currently empty.\n");
		return;
	}

	for (int i = 0; i < amount; i++) 
	{
		toPlayer->GetBuildingCardContainer()->push_back(pile->pop_back());
	}

	toPlayer->Send("You have receieved " + std::to_string(amount) + " building cards");
}

