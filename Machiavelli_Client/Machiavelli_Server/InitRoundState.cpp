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
	gm.GetCardManager()->GetDistrictCardDeck()->shuffle();

	for (int i{ 0 }; i < gm.GetPlayerList()->Size(); i++) {
		shared_ptr<Player> player = gm.GetPlayerList()->GetPlayerAt(i);

		player->GiveGoldPieces(2);

		GiveDistrictCardsFromDeck(player, gm.GetCardManager()->GetDistrictCardDeck(), 4);
	}

	context.setState(shared_ptr < IRoundState > {new CharacterSelectionState});
}

void InitRoundState::GiveDistrictCardsFromDeck(shared_ptr<Player> to, shared_ptr<CardDeck<DistrictCard>> pile, int amount)
{
	if (pile->size() < amount)
	{
		printf("Card stock depleted. gg\n");
		return;
	}

	for (int i{ 0 }; i < amount; i++)
	{
		to->GetDistrictCardContainer()->push_back(pile->pop_back());
	}
	to->Send("You have been given " + std::to_string(amount) + " district cards");
}

