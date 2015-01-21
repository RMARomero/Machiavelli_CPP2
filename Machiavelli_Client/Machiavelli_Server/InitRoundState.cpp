#include "InitRoundState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "CharacterSelectionState.h"

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

		player->GiveGoldPieces(2);

		GiveBuildingCardsFromDeck(player, gm.GetCardManager()->GetBuildingCardDeck(), 4);
	}

	context.setState(shared_ptr < IRoundState > {new CharacterSelectionState});
}

void InitRoundState::GiveBuildingCardsFromDeck(shared_ptr<Player> to, shared_ptr<CardDeck<BuildingCard>> pile, int amount)
{
	if (pile->size() < amount)
	{
		printf("Card stock is currently empty.\n");
		return;
	}

	for (int i = 0; i < amount; i++) 
	{
		to->GetBuildingCardContainer()->push_back(pile->pop_back());
	}

	to->Send("You have receieved " + std::to_string(amount) + " building cards");
}

