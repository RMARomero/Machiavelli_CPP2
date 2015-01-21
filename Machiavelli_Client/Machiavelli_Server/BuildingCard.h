#pragma once
#include "ICard.h"

enum CardColour { purple, yellow, red, blue, green };

class BuildingCard : public ICard
{
public:
	BuildingCard(string name, int cost, int points, CardColour colour);
	virtual ~BuildingCard(){}

	int getCost();

	CardColour getColour();
protected:
	int m_Cost;
	int m_Points;
	CardColour m_Colour;
};

