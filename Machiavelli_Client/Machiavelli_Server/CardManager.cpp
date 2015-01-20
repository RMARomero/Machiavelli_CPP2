#include "CardManager.h"
#include "CardPile.h"

CardManager::CardManager()
{
	
	m_DistrictCardPile = shared_ptr<CardPile<DistrictCard>> { new CardPile<DistrictCard> };
	m_DistrictCardDiscardPile = shared_ptr<CardPile<DistrictCard>> { new CardPile<DistrictCard> };
	m_CharacterCardPile = shared_ptr<CardPile<CharacterCard>> { new CardPile<CharacterCard> };
	m_CharacterCardDiscardPile = shared_ptr<CardPile<CharacterCard>> { new CardPile<CharacterCard> };


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

	m_CharacterCardPile->Push_Back(Assassin);
	m_CharacterCardPile->Push_Back(Thief);
	m_CharacterCardPile->Push_Back(Magician);
	m_CharacterCardPile->Push_Back(King);
	m_CharacterCardPile->Push_Back(Bishop);
	m_CharacterCardPile->Push_Back(Merchant);
	m_CharacterCardPile->Push_Back(Architect);
	m_CharacterCardPile->Push_Back(Warlord);

	CardReader reader("district_cards.csv");
	reader.parse();

	m_DistrictCardPile->AddCardPile(reader.getCards());
}

