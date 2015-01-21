#include "RoundFinishedState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "CharacterSelectionState.h"
RoundFinishedState::RoundFinishedState()
{
	printf("Round Finished State\n");
	/* Class that will check if the game is finished, by checking the bool method 'IsGameFinished' in the GameManager.
	If so, switch the GameManager state to 'FinishedState'

	(During this round, if someome gets his 8th building, mark the game as finished in the GameManager class by calling
	the method 'MarkAsFinished();')


	Also:
	Reset character cards;
	*/
}

void RoundFinishedState::Handle(GameRunningState& context, GameManager& gm)
{
	// discarded rounds terughalen
	vector<shared_ptr<CharacterCard>> discardedPile = gm.GetCardManager()->GetCharacterCardDiscardDeck()->TakeCardDeck();
	gm.GetCardManager()->GetCharacterCardDeck()->AddCardDeck(discardedPile);

	// karakterkaarten van iedereen afpakken en terug op de standaardlijst
	for (int i{ 0 }; i < gm.GetPlayerList()->Size(); i++) 
	{
		vector<shared_ptr<CharacterCard>> pile = gm.GetPlayerList()->GetPlayerAt(i)->GetCharacterCardContainer()->TakeCardDeck();

		for (auto &card : pile) 
		{
			gm.GetCardManager()->GetCharacterCardDeck()->push_back(card);
		}
	}

	// Afzien van iemand te doden of stelen als het niet gelukt is
	gm.setKilled(NotSet);
	gm.setRobbed(NotSet);


	// Has the game been finished?
	for (int i{ 0 }; i < gm.GetPlayerList()->Size(); i++) 
	{
		shared_ptr<Player> player = gm.GetPlayerList()->GetPlayerAt(i);

		if (player->GetBuildingCardContainer()->size() >= 8) 
		{
			gm.FinishGame();
			break;
		}
	}


	if (!gm.IsGameFinished()) 
	{
		// dit niet doen als de game gefinished is, obviously!
		context.setState(shared_ptr < IRoundState > { new CharacterSelectionState});
	}
}
