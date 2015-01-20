#include "DistrictCard.h"


DistrictCard::DistrictCard(string name, int cost, int points, CardColour colour)
{
	m_Name = name;
	m_Cost = cost;
	m_Points = points;
	m_Colour = colour;
}


DistrictCard::~DistrictCard()
{
}
