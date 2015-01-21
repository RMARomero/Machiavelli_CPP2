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
	gm.GetCardManager()->GetDistrictCardPile()->Shuffle();

	for (int i{ 0 }; i < gm.GetPlayerList()->Size(); i++) {
		shared_ptr<Player> player = gm.GetPlayerList()->GetPlayerAt(i);

		player->GiveGoldPieces(2);

		GiveDistrictCardsFromPile(player, gm.GetCardManager()->GetDistrictCardPile(), 4);
	}

	context.setState(shared_ptr < IRoundState > {new CharacterSelectionState});
}

void InitRoundState::GiveDistrictCardsFromPile(shared_ptr<Player> to, shared_ptr<CardPile<DistrictCard>> pile, int amount)
{
	if (pile->Size() < amount) 
	{
		printf("Card stock depleted. gg\n");
		return;
	}

	for (int i{ 0 }; i < amount; i++) 
	{
		to->GetDistrictCardContainer()->Push_Back(pile->Pop());
	}

	to->Send("You have been given " + std::to_string(amount) + " district cards");
}

