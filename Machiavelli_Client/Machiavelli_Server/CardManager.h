#pragma once
#define DISTRICT_CARD_DEPLETION_THRESHOLD 6
#include "CardPile.h"
#include "DistrictCard.h"
#include "CharacterCard.h"
#include "CardReader.h"

class CardManager
{
private:
	shared_ptr<CardPile<DistrictCard>> m_DistrictCardPile;
	shared_ptr<CardPile<DistrictCard>> m_DistrictCardDiscardPile;
	shared_ptr<CardPile<CharacterCard>> m_CharacterCardPile;
	shared_ptr<CardPile<CharacterCard>> m_CharacterCardDiscardPile;

	map<eCharacterCard, std::string> m_CharacterCardEnumToStringConversionMap;
public:
	CardManager();
	shared_ptr<CardPile<DistrictCard>> GetDistrictCardPile();
	shared_ptr<CardPile<DistrictCard>> GetDistrictCardDiscardPile();
	shared_ptr<CardPile<CharacterCard>> GetCharacterCardPile();
	shared_ptr<CardPile<CharacterCard>> GetCharacterCardDiscardPile();
	std::string CharacterEnumToString(eCharacterCard e);
	virtual ~CardManager();
};

