#pragma once
#include "ICard.h"

enum CardColour { purple, yellow, red, blue, green };

class DistrictCard : public ICard
{
public:
	DistrictCard(string name, int cost, int points, CardColour colour);
	virtual ~DistrictCard();

	int getCost();

	CardColour getColour();
protected:
	int m_Cost;
	int m_Points;
	CardColour m_Colour;
};

