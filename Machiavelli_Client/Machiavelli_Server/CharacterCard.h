#pragma once
#include "ICard.h"

enum eCharacterCard { Assassin, Thief, Magician, King, Bishop, Merchant, Architect, Warlord, NotSet };

class CharacterCard :
	public ICard
{
private:
	eCharacterCard m_Enum;
public:
	CharacterCard(string name, eCharacterCard characterEnum);
	eCharacterCard GetEnum();
	eCharacterCard GetEnumStringValue();
	virtual ~CharacterCard();
};


