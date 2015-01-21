#include "CharacterSelectionState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "AssassinState.h"

CharacterSelectionState::CharacterSelectionState()
{
	printf("Character Selection State\n");
}

void CharacterSelectionState::Handle(GameRunningState& context, GameManager& gm){
	gm.GetCardManager()->GetCharacterCardDeck()->shuffle();

	//gm.GetCardManager()->GetCharacterCardPile()->Pop();

	string newRoundLine1 = "\n-----------------------------------------------------\n";
	string newRoundLine2 =   "--------------------- NEW ROUND ---------------------\n";
	string newRoundLine3 =   "-----------------------------------------------------";
	gm.GetPlayerList()->SendAll(newRoundLine1 + newRoundLine2 + newRoundLine3);

	int AmountOfPlayers = gm.GetPlayerList()->Size();

	int i = 0;
	while (gm.GetCardManager()->GetCharacterCardDeck()->size() > 1)
	{
		shared_ptr<Player> currentPlayer = gm.GetPlayerList()->GetPlayerAt(i % AmountOfPlayers);
		gm.GetPlayerList()->SendAllBut(currentPlayer, "\n" + currentPlayer->GetName() + " is picking a Character Card, please wait...\n");

		shared_ptr<CardDeck<CharacterCard>> characterCardPile = gm.GetCardManager()->GetCharacterCardDeck();
		if (i == 0) 
		{
			gm.GetCardManager()->GetCharacterCardDiscardDeck()->push_back(characterCardPile->pop_back());
		}
		else
		{
			vector<string> answers;
			for (int i = 0; i < characterCardPile->size(); i++)
			{
				answers.push_back(characterCardPile->at(i)->getName());
			}
			int result = currentPlayer->RequestInput("\nWhich card would you like to discard?", answers);
			gm.GetCardManager()->GetCharacterCardDiscardDeck()->push_back(characterCardPile->take(result));
		}

		vector<string> answers;
		int pileSize = characterCardPile->size();
		int result = 0;
		if (pileSize > 1)
		{
			for (int i = 0; i < pileSize; i++)
			{
				shared_ptr<ICard> card = characterCardPile->at(i);
				answers.push_back(card->getName());
			}
			result = currentPlayer->RequestInput("\nWhich card would you like to keep?", answers);
		}
		else
		{
			//Maybe a message, that you automatically got the last card.. but w/e, doubt its needed
		}
		currentPlayer->GetCharacterCardContainer()->push_back(characterCardPile->take(result));
		i++;
	}
	context.setState(shared_ptr < IRoundState > {new AssassinState});

}


