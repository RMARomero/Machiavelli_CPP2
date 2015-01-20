#pragma once
#include "ICard.h"

enum CardColour { purple, yellow, red, blue, green };

class DistrictCard :
	public ICard
{
protected:
	int m_Cost;
	int m_Points;
	CardColour m_Colour;
	
public:
	DistrictCard(string name, int cost, int points, CardColour colour);
	virtual ~DistrictCard();

	int getCost() { return m_Cost; };

	CardColour GetColour() { return m_Colour; };

};

