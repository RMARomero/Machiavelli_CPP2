#pragma once
#include "ICard.h"

enum eCharacterCard { Assassin, Thief, Magician, King, Bishop, Merchant, Architect, Warlord, NotSet };

class CharacterCard : public ICard
{
public:
	CharacterCard(string name, eCharacterCard characterEnum);
	virtual ~CharacterCard(){}
	eCharacterCard GetEnum() { return m_Enum; }
	eCharacterCard GetEnumStringValue();

private:
	eCharacterCard m_Enum;
};


