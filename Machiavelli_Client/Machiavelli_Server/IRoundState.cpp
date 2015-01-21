#include "IRoundState.h"
#include "GameManager.h"
#include "CardManager.h"

void IRoundState::Handle(GameRunningState& context, GameManager& gm)
{
	m_CurrentPlayer = gm.GetPlayerList()->GetPlayerByRole(currentRole());
	
	if (m_CurrentPlayer != nullptr)
	{
		m_CurrentPlayer->Send("\n"+gm.GetCardManager()->CharacterEnumToString(currentRole()) + "'s turn:\n");
		gm.GetPlayerList()->SendAllBut(m_CurrentPlayer, "\n" + gm.GetCardManager()->CharacterEnumToString(currentRole()) + "'s turn, please wait...\n");
	}
	else
	{
		gm.GetPlayerList()->SendAll("\n" + gm.GetCardManager()->CharacterEnumToString(currentRole()) + "'s turn, please wait...\n");
	}

	if (m_CurrentPlayer == nullptr || gm.isKilled(currentRole())) 
	{
		gm.GetPlayerList()->SendAll("Hmm... nothing happened.");
		return;
	}

	RefillDistrictCardPileIfDepleted(gm.GetCardManager(), DISTRICT_CARD_DEPLETION_THRESHOLD);

	m_CurrentPlayer->ShowStats();

	if (gm.isRobbed(currentRole())) 
	{
		shared_ptr<Player> thief = gm.GetPlayerList()->GetPlayerByRole(Thief);
		int loot = m_CurrentPlayer->GetGoldPieces();
		m_CurrentPlayer->SetGoldPieces(0);
		thief->GiveGoldPieces(loot);

		thief->Send("Your stolen goods are " + std::to_string(loot) + "gold");
		m_CurrentPlayer->Send("You have been robbed and lost all your gold");
	}

	vector<string> answers = { "Receive 2 gold", "Receive building card" };
	int result = m_CurrentPlayer->RequestInput("Please select one.", answers);

	switch (result) 
	{
		case 0:
		{
			m_CurrentPlayer->GiveGoldPieces(2);
			m_CurrentPlayer->Send("You receive 2 gold.");
			break;
		}
		case 1:
		{
			// rekening houden met een lege stapel!
			shared_ptr<CardPile<DistrictCard>> cp = gm.GetCardManager()->GetDistrictCardPile();

			if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Observatorium")) 
			{
				PickDistrictCard(cp,3);
			}
			else 
			{
				PickDistrictCard(cp, 2);
			}
			break;
		}
	}

	if (m_CurrentPlayer->GetDistrictCardContainer()->Size() > 0) 
	{
		int result = m_CurrentPlayer->RequestInput("Would you like to build something?", vector < string > {"Yes", "No"});

		if (result == 1)
			return;

		BuildSomething();
	}

	if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Laboratorium") && m_CurrentPlayer->GetDistrictCardContainer()->Size() >= 1) 
	{
		int result = m_CurrentPlayer->RequestInput("Would you like to make use of your special ability to return one of your cards?", vector < string > {"Yes", "No"});

		if (result == 1)
			return;

		int cardIndex = m_CurrentPlayer->RequestInput("Which card would you like to return?", m_CurrentPlayer->GetDistrictCardContainer()->ToVector());

		shared_ptr<DistrictCard> card = m_CurrentPlayer->GetDistrictCardContainer()->Take(cardIndex);
		gm.GetCardManager()->GetDistrictCardDiscardPile()->Push_Back(card);

		m_CurrentPlayer->GiveGoldPieces(1);
	}

	if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Werkplaats") && m_CurrentPlayer->GetGoldPieces() >= 3) 
	{
		int answer = m_CurrentPlayer->RequestInput("Would you like to make use of the Werkplaats and buy some cards?", vector < string > {"yes", "no"});
		
		if (answer == 0) 
		{
			for (int i{ 0 }; i < 2; i++) 
			{
				shared_ptr<DistrictCard> card = gm.GetCardManager()->GetDistrictCardPile()->Pop();
				m_CurrentPlayer->Send("You picked a " + card->getName());
				m_CurrentPlayer->GetDistrictCardContainer()->Push_Back(card);
			}
		}
	}

	if (m_CurrentPlayer->GetCityCardContainer()->Size() >= 8 && gm.get8Buildings().get() == nullptr) 
	{
		gm.set8Buildings(m_CurrentPlayer);
	}
}


void IRoundState::PickDistrictCard(shared_ptr<CardPile<DistrictCard>> cp, int amount) 
{
	if (cp->Size() <= 0) 
	{
		m_CurrentPlayer->Send("Sorry, building card pile is empty. You receive nothing.");
		return;
	}

	int options = min(cp->Size(), amount);
	vector<shared_ptr<DistrictCard>> choices;

	for (int i{ 0 }; i < options; i++) 
	{
		choices.push_back(cp->Pop());
	}

	if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Bibliotheek")) 
	{
		m_CurrentPlayer->Send("You have a library, so you can keep " + std::to_string(amount) + " cards");
		for (auto &card : choices) 
		{
			m_CurrentPlayer->GetDistrictCardContainer()->Push_Back(card);
			m_CurrentPlayer->Send("You picked a " + card->getName());
		}
	}
	else 
	{
		vector<string> answers;

		for (auto &card : choices) 
		{
			answers.push_back(card->getName());
		}

		int result = m_CurrentPlayer->RequestInput("Which card would you like to keep?", answers);

		for (auto &card : choices) 
		{
			if (card.get() == choices.at(result).get()) 
			{
				m_CurrentPlayer->GetDistrictCardContainer()->Push_Back(card);
				m_CurrentPlayer->Send("You picked a " + card->getName());
			}
			else 
			{
				cp->Push_Back(card);
			}
		}
	}
}

void IRoundState::RefillDistrictCardPileIfDepleted(shared_ptr<CardManager> cm, int threshold) 
{
	if (cm->GetDistrictCardPile()->Size() < threshold) 
	{
		for (int i{ 0 }; i < cm->GetCharacterCardDiscardPile()->Size(); i++) 
		{
			cm->GetDistrictCardPile()->Push_Back(cm->GetDistrictCardDiscardPile()->Pop());
		}
		cm->GetDistrictCardPile()->Shuffle();
	}
}

void IRoundState::BuildSomething() 
{
	int wallet = m_CurrentPlayer->GetGoldPieces();

	vector<string> answers;

	for (int i{ 0 }; i < m_CurrentPlayer->GetDistrictCardContainer()->Size(); i++) 
	{
		shared_ptr<DistrictCard> card = m_CurrentPlayer->GetDistrictCardContainer()->At(i);

		answers.push_back(card->getName() + " - Price: " + std::to_string(card->getCost()));
	}

	int result2 = m_CurrentPlayer->RequestInput("What do you want to build? [wallet: " + std::to_string(wallet) + "gp]", answers);
	shared_ptr<DistrictCard> cardToUse = m_CurrentPlayer->GetDistrictCardContainer()->Take(result2);

	if (cardToUse->getCost() > wallet)
	{
		m_CurrentPlayer->GetDistrictCardContainer()->Push_Back(cardToUse);
		m_CurrentPlayer->Send("Whoops, you do not have enough money!");
	}
	else 
	{
		m_CurrentPlayer->SetGoldPieces(m_CurrentPlayer->GetGoldPieces() - cardToUse->getCost());
		m_CurrentPlayer->GetCityCardContainer()->Push_Back(cardToUse);
		m_CurrentPlayer->Send(cardToUse->getName() + " has been added to your city!");
	}
}