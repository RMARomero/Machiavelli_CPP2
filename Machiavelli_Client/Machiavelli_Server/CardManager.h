#pragma once
#define DISTRICT_CARD_DEPLETION_THRESHOLD 6
#include "CardDeck.h"
#include "BuildingCard.h"
#include "CharacterCard.h"
#include "CardReader.h"

class CardManager
{
public:
	CardManager();
	virtual ~CardManager(){}

	shared_ptr<CardDeck<BuildingCard>> GetBuildingCardDeck(){ return m_BuildingCardDeck; }
	shared_ptr<CardDeck<BuildingCard>> GetBuildingCardDiscardDeck(){ return m_BuildingCardDiscardDeck; }
	shared_ptr<CardDeck<CharacterCard>> GetCharacterCardDeck(){ return m_CharacterCardDeck; }
	shared_ptr<CardDeck<CharacterCard>> GetCharacterCardDiscardDeck(){ return m_CharacterCardDiscardDeck; }

	std::string CharacterEnumToString(eCharacterCard e){ return m_CharacterCardEnumToStringConversionMap[e]; }

private:
	shared_ptr<CardDeck<BuildingCard>> m_BuildingCardDeck;
	shared_ptr<CardDeck<BuildingCard>> m_BuildingCardDiscardDeck;
	shared_ptr<CardDeck<CharacterCard>> m_CharacterCardDeck;
	shared_ptr<CardDeck<CharacterCard>> m_CharacterCardDiscardDeck;

	map<eCharacterCard, std::string> m_CharacterCardEnumToStringConversionMap;
};

