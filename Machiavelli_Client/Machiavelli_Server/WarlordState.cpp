#include "WarlordState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "RoundFinishedState.h"

WarlordState::WarlordState()
{
	printf("Warlord State\n");
}

void WarlordState::Handle(GameRunningState& context, GameManager& gm)
{
	IRoundState::Handle(context, gm);
	if (m_CurrentPlayer.get() == nullptr || gm.isKilled(currentRole())) 
	{
		context.setState(unique_ptr < IRoundState > {new RoundFinishedState});
		return;
	}

	m_CurrentPlayer->GiveGPForCards(red);
	
	vector<string> victims;
	for (int i{ 0 }; i < gm.GetPlayerList()->Size(); i++) 
	{
		victims.push_back(gm.GetPlayerList()->GetPlayerAt(i)->GetName());
	}

	int result = m_CurrentPlayer->RequestInput("Select which player's buildings you would like to target.", victims);

	shared_ptr<Player> choosenVictim = gm.GetPlayerList()->GetPlayerAt(result);

	if (choosenVictim.get() == m_CurrentPlayer.get()) 
	{
		m_CurrentPlayer->Send("You cannot attack yourself.");
		return;
	}

	if (choosenVictim->HasCharacterCard(Bishop)) 
	{
		m_CurrentPlayer->Send("You cannot attack the bishop.");
		context.setState(unique_ptr <IRoundState> {new RoundFinishedState});
		return;
	}

	vector<string> destroyables;

	for (int i{ 0 }; i < choosenVictim->GetCityCardContainer()->size(); i++) 
	{
		shared_ptr<BuildingCard> card = choosenVictim->GetCityCardContainer()->at(i);

		destroyables.push_back(card->getName() + " costs to destroy: " + std::to_string(card->getCost() - 1));
	}

	if (!destroyables.empty()) 
	{
		int choice = m_CurrentPlayer->RequestInput("Select which building you want to destroy. You currently have: " + std::to_string(m_CurrentPlayer->GetGoldPieces()) + " gold", destroyables);

		shared_ptr<BuildingCard> removedCard = choosenVictim->GetCityCardContainer()->take(choice);

		if (removedCard->getCost() - 1 > m_CurrentPlayer->GetGoldPieces() || removedCard->getName() == "Kerker") 
		{
			m_CurrentPlayer->Send("You cannot do this!");
			choosenVictim->GetCityCardContainer()->push_back(removedCard);
		}
		else 
		{

			if (choosenVictim->GetCityCardContainer()->HasCard("Kerkhof") && choosenVictim->GetGoldPieces() >= 1) 
			{
				int action = choosenVictim->RequestInput("The building " + removedCard->getName() + " is about to be destroyed. Would you like to keep it?", vector < string > { "yes", "no"});

				if (action == 0) 
				{
					choosenVictim->GetDistrictCardContainer()->Push_Back(removedCard);
					choosenVictim->Send("The card has been added to your card pile");
				}
				else 
				{
					gm.GetCardManager()->GetBuildingCardDiscardDeck()->push_back(removedCard);
				}

			}
			else 
			{
				gm.GetCardManager()->GetBuildingCardDiscardDeck()->push_back(removedCard);
				choosenVictim->Send("You building " + removedCard->getName() + " has been destroyed by " + m_CurrentPlayer->GetName());
			}
		
			m_CurrentPlayer->SetGoldPieces(m_CurrentPlayer->GetGoldPieces() - (removedCard->getCost() - 1));
			m_CurrentPlayer->Send("Building destroyed!");
		}
	}
	else 
	{
		m_CurrentPlayer->Send("There is nothing to destroy.");
	}
	context.setState(unique_ptr < IRoundState > {new RoundFinishedState});
}
