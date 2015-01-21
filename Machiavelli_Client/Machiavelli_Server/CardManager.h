#pragma once
#define DISTRICT_CARD_DEPLETION_THRESHOLD 6
#include "CardDeck.h"
#include "DistrictCard.h"
#include "CharacterCard.h"
#include "CardReader.h"

class CardManager
{
public:
	CardManager();
	virtual ~CardManager(){}

	shared_ptr<CardDeck<DistrictCard>> GetDistrictCardDeck(){ return m_DistrictCardDeck; }
	shared_ptr<CardDeck<DistrictCard>> GetDistrictCardDiscardDeck(){ return m_DistrictCardDiscardDeck; }
	shared_ptr<CardDeck<CharacterCard>> GetCharacterCardDeck(){ return m_CharacterCardDeck; }
	shared_ptr<CardDeck<CharacterCard>> GetCharacterCardDiscardDeck(){ return m_CharacterCardDiscardDeck; }

	std::string CharacterEnumToString(eCharacterCard e){ return m_CharacterCardEnumToStringConversionMap[e]; }

private:
	shared_ptr<CardDeck<DistrictCard>> m_DistrictCardDeck;
	shared_ptr<CardDeck<DistrictCard>> m_DistrictCardDiscardDeck;
	shared_ptr<CardDeck<CharacterCard>> m_CharacterCardDeck;
	shared_ptr<CardDeck<CharacterCard>> m_CharacterCardDiscardDeck;

	map<eCharacterCard, std::string> m_CharacterCardEnumToStringConversionMap;
};

