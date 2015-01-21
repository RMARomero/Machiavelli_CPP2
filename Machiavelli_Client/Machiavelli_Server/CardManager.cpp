#include "CardManager.h"
#include "CardDeck.h"

CardManager::CardManager()
{
	
	m_BuildingCardDeck = shared_ptr<CardDeck<BuildingCard>> { new CardDeck<BuildingCard> };
	m_BuildingCardDiscardDeck = shared_ptr<CardDeck<BuildingCard>> { new CardDeck<BuildingCard> };
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

	CardReader reader("character_cards.csv");// move this above to parse characters
	reader.parseCharacters();

	m_CharacterCardDeck->AddCardDeck(reader.getCharCards());

	m_CharacterCardDeck->shuffle();

	reader.setFilePath("building_cards.csv");
	reader.parse();

	m_BuildingCardDeck->AddCardDeck(reader.getCards());

	m_BuildingCardDeck->shuffle();
}

