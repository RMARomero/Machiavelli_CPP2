#include "CharacterSelectionState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "AssassinState.h"

CharacterSelectionState::CharacterSelectionState()
{
	printf("Character Selection State\n");
}

CharacterSelectionState::~CharacterSelectionState()
{
}

void CharacterSelectionState::Handle(GameRunningState& context, GameManager& gm)
{
	gm.GetCardManager()->GetCharacterCardPile()->Shuffle();

	//gm.GetCardManager()->GetCharacterCardPile()->Pop();

	string newRoundln = "\n\t== Machiavelli: New Round started! ==\n";
	gm.GetPlayerList()->SendAll(newRoundln);

	int AmountOfPlayers = gm.GetPlayerList()->Size();

	int i = 0;
	while (gm.GetCardManager()->GetCharacterCardPile()->Size() > 1)
	{
		shared_ptr<Player> currentPlayer = gm.GetPlayerList()->GetPlayerAt(i % AmountOfPlayers);
		gm.GetPlayerList()->SendAllBut(currentPlayer, "\n" + currentPlayer->GetName() + " is busy picking a character.\n");

		shared_ptr<CardPile<CharacterCard>> characterCardPile = gm.GetCardManager()->GetCharacterCardPile();
		if (i == 0) 
		{
			gm.GetCardManager()->GetCharacterCardDiscardPile()->Push_Back(characterCardPile->Pop());
		}
		else
		{
			vector<string> answers;
			for (int i = 0; i < characterCardPile->Size(); i++)
			{
				answers.push_back(characterCardPile->At(i)->getName());
			}
			int result = currentPlayer->RequestInput("\nWhich card would you like to discard?", answers);
			gm.GetCardManager()->GetCharacterCardDiscardPile()->Push_Back(characterCardPile->Take(result));
		}

		vector<string> answers;
		int pileSize = characterCardPile->Size();
		int result = 0;
		if (pileSize > 1)
		{
			for (int i = 0; i < pileSize; i++)
			{
				shared_ptr<ICard> card = characterCardPile->At(i);

				answers.push_back(card->getName());
			}
			result = currentPlayer->RequestInput("\nWhich card would you like to keep?", answers);
		}

		currentPlayer->GetCharacterCardContainer()->Push_Back(characterCardPile->Take(result));
		i++;
	}

	context.setState(shared_ptr < IRoundState > {new AssassinState});

}


