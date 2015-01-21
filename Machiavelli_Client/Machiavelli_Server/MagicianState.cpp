#include "MagicianState.h"
#include "GameManager.h"
#include "CardDeck.h"
#include "GameRunningState.h"
#include "KingState.h"

MagicianState::MagicianState()
{
	printf("Magician State\n");
}

void MagicianState::Handle(GameRunningState& context, GameManager& gm)
{
	IRoundState::Handle(context, gm);
	if (m_CurrentPlayer.get() == nullptr || gm.isKilled(currentRole())) 
	{
		context.setState(unique_ptr < IRoundState > {new KingState});
		return;
	}
	vector<string> answers = { "Switch cards with another player", "Dispose of cards & get district cards" };
	int result = m_CurrentPlayer->RequestInput("Make a choice, Magician:", answers);

	switch (result) 
	{
	case 0:
	{
		vector<string> playerList;
		for (int i = 0; i < gm.GetPlayerList()->Size(); i++) 
		{
			if (gm.GetPlayerList()->GetPlayerAt(i) == m_CurrentPlayer) //swicthing with yourself...
			{
				playerList.push_back(gm.GetPlayerList()->GetPlayerAt(i)->GetName() + "\t (This is you)");
			}
			else
			{
				playerList.push_back(gm.GetPlayerList()->GetPlayerAt(i)->GetName());
			}
		}

		int playerPos = m_CurrentPlayer->RequestInput("Select a player who's card you would like.", playerList);
		shared_ptr<Player> victim = gm.GetPlayerList()->GetPlayerAt(playerPos);

		if (victim != m_CurrentPlayer)
		{
			vector<shared_ptr<BuildingCard>> victimPile = victim->GetBuildingCardContainer()->TakeCardDeck();
			vector<shared_ptr<BuildingCard>> myPile = m_CurrentPlayer->GetBuildingCardContainer()->TakeCardDeck();
	
			victim->GetBuildingCardContainer()->AddCardDeck(myPile);
			m_CurrentPlayer->GetBuildingCardContainer()->AddCardDeck(victimPile);

			victim->Send("You have switched cards with " + m_CurrentPlayer->GetName());
			m_CurrentPlayer->Send("You have switched cards with " + victim->GetName());
		}
		else
		{
			m_CurrentPlayer->Send("\nYou cannot switch with yourself.");
		}


		context.setState(shared_ptr<IRoundState> { new KingState });

		break;
	}
	case 1:
		if (m_CurrentPlayer->GetBuildingCardContainer()->size() <= 0) 
		{
			m_CurrentPlayer->Send("You do not posses any cards which you can return.");
		}
		else 
		{
			
			int requestedCards = 0;
			int answer = -1;
			vector<string> choices;

			do 
			{
				choices = m_CurrentPlayer->GetBuildingCardContainer()->to_vector();
				choices.push_back("I'm finished!");

				answer = m_CurrentPlayer->RequestInput("Choose which cards you want to discard.", choices);

				if (answer != choices.size() - 1) 
				{
					shared_ptr<BuildingCard> removedCard = m_CurrentPlayer->GetBuildingCardContainer()->take(answer);
					gm.GetCardManager()->GetBuildingCardDiscardDeck()->push_back(removedCard);

					requestedCards++;
				}
			} while (answer != (choices.size() - 1));

			int cardsToGive = min(requestedCards, gm.GetCardManager()->GetBuildingCardDeck()->size());

			for (int i{ 0 }; i < cardsToGive; i++) 
			{
				m_CurrentPlayer->GetBuildingCardContainer()->push_back(gm.GetCardManager()->GetBuildingCardDeck()->pop_back());
			}

			m_CurrentPlayer->Send("You received " + std::to_string(cardsToGive) + " new cards");
		}
		context.setState(shared_ptr<IRoundState> { new KingState });
		break;
	}

}
