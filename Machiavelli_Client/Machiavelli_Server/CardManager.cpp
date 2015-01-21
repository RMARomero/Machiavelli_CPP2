#include "CardManager.h"
#include "CardDeck.h"

CardManager::CardManager()
{
	
	m_DistrictCardDeck = shared_ptr<CardDeck<DistrictCard>> { new CardDeck<DistrictCard> };
	m_DistrictCardDiscardDeck = shared_ptr<CardDeck<DistrictCard>> { new CardDeck<DistrictCard> };
	m_CharacterCardDeck = shared_ptr<CardDeck<CharacterCard>> { new CardDeck<CharacterCard> };
	m_CharacterCardDiscardDeck = shared_ptr<CardDeck<CharacterCard>> { new CardDeck<CharacterCard> };


	m_CharacterCardEnumToStringConversionMap[Assassin] = "Assassin";
	m_CharacterCardEnumToStringConversionMap[Thief] = "Thief";
	m_CharacterCardEnumToStringConversionMap[Magician] = "Magician";
	m_CharacterCardEnumToStringConversionMap[King] = "King";
	m_CharacterCardEnumToStringConversionMap[Bishop] = "Bishop";
	m_CharacterCardEnumToStringConversionMap[Merchant] = "Merchant";
	m_CharacterCardEnumToStringConversionMap[Architect] = "Architect";
	m_CharacterCardEnumToStringConversionMap[Warlord] = "Warlord";

	//TODO: Create all cards
	
	shared_ptr<CharacterCard> Assassin{ new CharacterCard("Assassin", eCharacterCard::Assassin) };
	shared_ptr<CharacterCard> Thief{ new CharacterCard("Thief", eCharacterCard::Thief) };
	shared_ptr<CharacterCard> Magician{ new CharacterCard("Magician", eCharacterCard::Magician) };
	shared_ptr<CharacterCard> King{ new CharacterCard("King", eCharacterCard::King) };
	shared_ptr<CharacterCard> Bishop{ new CharacterCard("Bishop", eCharacterCard::Bishop) };
	shared_ptr<CharacterCard> Merchant{ new CharacterCard("Merchant", eCharacterCard::Merchant) };
	shared_ptr<CharacterCard> Architect{ new CharacterCard("Architect", eCharacterCard::Architect) };
	shared_ptr<CharacterCard> Warlord{ new CharacterCard("Warlord", eCharacterCard::Warlord) };

	m_CharacterCardDeck->push_back(Assassin);
	m_CharacterCardDeck->push_back(Thief);
	m_CharacterCardDeck->push_back(Magician);
	m_CharacterCardDeck->push_back(King);
	m_CharacterCardDeck->push_back(Bishop);
	m_CharacterCardDeck->push_back(Merchant);
	m_CharacterCardDeck->push_back(Architect);
	m_CharacterCardDeck->push_back(Warlord);

	CardReader reader("district_cards.csv");
	reader.parse();

	m_DistrictCardDeck->AddCardDeck(reader.getCards());
}

