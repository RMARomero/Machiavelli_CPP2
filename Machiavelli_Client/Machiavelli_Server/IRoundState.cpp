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

	RefillDistrictCardDeckIfDepleted(gm.GetCardManager(), DISTRICT_CARD_DEPLETION_THRESHOLD);

	m_CurrentPlayer->ShowStats();

	if (gm.isRobbed(currentRole())) 
	{
		shared_ptr<Player> thief = gm.GetPlayerList()->GetPlayerByRole(Thief);
		int loot = m_CurrentPlayer->GetGoldPieces();
		m_CurrentPlayer->SetGoldPieces(0);
		thief->GiveGoldPieces(loot);

		thief->Send("Your illegally obtained loot is " + std::to_string(loot) + "gp");
		m_CurrentPlayer->Send("You have been robbed and lost all your gp (If you had any :P)");
	}

	vector<string> answers = { "Receive 2 goldpieces", "Receive district card" };
	int result = m_CurrentPlayer->RequestInput("What do you want to do?", answers);

	switch (result) 
	{
		case 0:
		{
			m_CurrentPlayer->GiveGoldPieces(2);
			m_CurrentPlayer->Send("You receive 2 goldpieces.");
			break;
		}
		case 1:
		{
			// rekening houden met een lege stapel!
			shared_ptr<CardDeck<DistrictCard>> cp = gm.GetCardManager()->GetDistrictCardDeck();

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

	if (m_CurrentPlayer->GetDistrictCardContainer()->size() > 0) 
	{
		int result = m_CurrentPlayer->RequestInput("Would you like to build something?", vector < string > {"Yes", "No"});

		if (result == 1)
			return;

		BuildSomething();
	}

	if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Laboratorium") && m_CurrentPlayer->GetDistrictCardContainer()->size() >= 1) 
	{
		int result = m_CurrentPlayer->RequestInput("Would you like to make use of your special ability to return one of your cards?", vector < string > {"Yes", "No"});

		if (result == 1)
			return;

		int cardIndex = m_CurrentPlayer->RequestInput("Which card would you like to return?", m_CurrentPlayer->GetDistrictCardContainer()->to_vector());

		shared_ptr<DistrictCard> card = m_CurrentPlayer->GetDistrictCardContainer()->take(cardIndex);
		gm.GetCardManager()->GetDistrictCardDiscardDeck()->push_back(card);

		m_CurrentPlayer->GiveGoldPieces(1);
	}

	if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Werkplaats") && m_CurrentPlayer->GetGoldPieces() >= 3) 
	{
		int answer = m_CurrentPlayer->RequestInput("Would you like to make use of the Werkplaats and buy some cards?", vector < string > {"yes", "no"});
		
		if (answer == 0) 
		{
			for (int i{ 0 }; i < 2; i++) 
			{
				shared_ptr<DistrictCard> card = gm.GetCardManager()->GetDistrictCardDeck()->pop_back();
				m_CurrentPlayer->Send("You picked a " + card->getName());
				m_CurrentPlayer->GetDistrictCardContainer()->push_back(card);
			}
		}
	}


	if (m_CurrentPlayer->GetCityCardContainer()->size() >= 8 && gm.get8Buildings().get() == nullptr) 
	{
		gm.set8Buildings(m_CurrentPlayer);
	}
}


void IRoundState::PickDistrictCard(shared_ptr<CardDeck<DistrictCard>> cp, int amount) 
{
	if (cp->size() <= 0) 
	{
		m_CurrentPlayer->Send("Sorry, district card pile is empty. You receive nothing. #getRekt");
		return;
	}

	int options = min(cp->size(), amount);
	vector<shared_ptr<DistrictCard>> choices;

	for (int i{ 0 }; i < options; i++) 
	{
		choices.push_back(cp->pop_back());
	}

	if (m_CurrentPlayer->GetCityCardContainer()->HasCard("Bibliotheek")) 
	{
		m_CurrentPlayer->Send("You have a library, so you can keep " + std::to_string(amount) + " cards");
		for (auto &card : choices) 
		{
			m_CurrentPlayer->GetDistrictCardContainer()->push_back(card);
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
				m_CurrentPlayer->GetDistrictCardContainer()->push_back(card);
				m_CurrentPlayer->Send("You picked a " + card->getName());
			}
			else 
			{
				cp->push_back(card);
			}
		}
	}
}

void IRoundState::RefillDistrictCardDeckIfDepleted(shared_ptr<CardManager> cm, int threshold) 
{
	if (cm->GetDistrictCardDeck()->size() < threshold) 
	{
		for (int i{ 0 }; i < cm->GetCharacterCardDiscardDeck()->size(); i++) 
		{
			cm->GetDistrictCardDeck()->push_back(cm->GetDistrictCardDiscardDeck()->pop_back());
		}

		cm->GetDistrictCardDeck()->shuffle();
	}
}

void IRoundState::BuildSomething() 
{
	int wallet = m_CurrentPlayer->GetGoldPieces();

	vector<string> answers;

	for (int i{ 0 }; i < m_CurrentPlayer->GetDistrictCardContainer()->size(); i++) 
	{
		shared_ptr<DistrictCard> card = m_CurrentPlayer->GetDistrictCardContainer()->at(i);

		answers.push_back(card->getName() + " - Price: " + std::to_string(card->getCost()));
	}

	int result2 = m_CurrentPlayer->RequestInput("What do you want to build? [wallet: " + std::to_string(wallet) + "gp]", answers);
	shared_ptr<DistrictCard> cardToUse = m_CurrentPlayer->GetDistrictCardContainer()->take(result2);

	if (cardToUse->getCost() > wallet)
	{
		m_CurrentPlayer->GetDistrictCardContainer()->push_back(cardToUse);
		m_CurrentPlayer->Send("Whoops, you do not have enough money!");
	}
	else 
	{
		m_CurrentPlayer->SetGoldPieces(m_CurrentPlayer->GetGoldPieces() - cardToUse->getCost());
		m_CurrentPlayer->GetCityCardContainer()->push_back(cardToUse);
		m_CurrentPlayer->Send(cardToUse->getName() + " has been added to your city!");
	}
}