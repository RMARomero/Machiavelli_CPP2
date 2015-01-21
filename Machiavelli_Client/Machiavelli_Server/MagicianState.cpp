#include "MagicianState.h"
#include "GameManager.h"
#include "CardPile.h"
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
			vector<shared_ptr<DistrictCard>> victimPile = victim->GetDistrictCardContainer()->TakeCardPile();
			vector<shared_ptr<DistrictCard>> myPile = m_CurrentPlayer->GetDistrictCardContainer()->TakeCardPile();
	
			victim->GetDistrictCardContainer()->AddCardPile(myPile);
			m_CurrentPlayer->GetDistrictCardContainer()->AddCardPile(victimPile);

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
		if (m_CurrentPlayer->GetDistrictCardContainer()->Size() <= 0) 
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
				choices = m_CurrentPlayer->GetDistrictCardContainer()->ToVector();
				choices.push_back("I'm finished!");

				answer = m_CurrentPlayer->RequestInput("Choose which cards you want to discard.", choices);

				if (answer != choices.size() - 1) 
				{
					shared_ptr<DistrictCard> removedCard = m_CurrentPlayer->GetDistrictCardContainer()->Take(answer);
					gm.GetCardManager()->GetDistrictCardDiscardPile()->Push_Back(removedCard);

					requestedCards++;
				}
			} while (answer != (choices.size() - 1));

			int cardsToGive = min(requestedCards, gm.GetCardManager()->GetDistrictCardPile()->Size());

			for (int i{ 0 }; i < cardsToGive; i++) 
			{
				m_CurrentPlayer->GetDistrictCardContainer()->Push_Back(gm.GetCardManager()->GetDistrictCardPile()->Pop());
			}

			m_CurrentPlayer->Send("You received " + std::to_string(cardsToGive) + " new cards");

		}
		context.setState(shared_ptr<IRoundState> { new KingState });
		break;
	}

}
