#pragma once
#define DISTRICT_CARD_DEPLETION_THRESHOLD 6
#include "CardPile.h"
#include "DistrictCard.h"
#include "CharacterCard.h"
#include "CardReader.h"

class CardManager
{
public:
	CardManager();
	virtual ~CardManager(){}

	shared_ptr<CardPile<DistrictCard>> GetDistrictCardPile(){ return m_DistrictCardPile;	}
	shared_ptr<CardPile<DistrictCard>> GetDistrictCardDiscardPile(){ return m_DistrictCardDiscardPile; }
	shared_ptr<CardPile<CharacterCard>> GetCharacterCardPile(){	return m_CharacterCardPile;	}
	shared_ptr<CardPile<CharacterCard>> GetCharacterCardDiscardPile(){ return m_CharacterCardDiscardPile; }

	std::string CharacterEnumToString(eCharacterCard e){ return m_CharacterCardEnumToStringConversionMap[e]; }

private:
	shared_ptr<CardPile<DistrictCard>> m_DistrictCardPile;
	shared_ptr<CardPile<DistrictCard>> m_DistrictCardDiscardPile;
	shared_ptr<CardPile<CharacterCard>> m_CharacterCardPile;
	shared_ptr<CardPile<CharacterCard>> m_CharacterCardDiscardPile;

	map<eCharacterCard, std::string> m_CharacterCardEnumToStringConversionMap;
};

