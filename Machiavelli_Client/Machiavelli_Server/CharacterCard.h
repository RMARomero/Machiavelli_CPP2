#pragma once
#include "ICard.h"

enum eCharacterCard { Assassin, Thief, Magician, King, Bishop, Merchant, Architect, Warlord, NotSet };

class CharacterCard : public ICard
{
public:
	CharacterCard(string name, eCharacterCard characterEnum);
	eCharacterCard GetEnum();
	eCharacterCard GetEnumStringValue();
	virtual ~CharacterCard();

private:
	eCharacterCard m_Enum;
};


