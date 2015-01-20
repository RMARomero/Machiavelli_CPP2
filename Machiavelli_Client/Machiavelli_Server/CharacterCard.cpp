#include "CharacterCard.h"


CharacterCard::CharacterCard(string name, eCharacterCard characterEnum): m_Enum(characterEnum)
{
	m_Name = name;
}


eCharacterCard CharacterCard::GetEnum(){
	return m_Enum;
}

CharacterCard::~CharacterCard()
{
}
