#include "BuildingCard.h"

BuildingCard::BuildingCard(string name, int cost, int points, CardColour colour)
{
	m_Name = name;
	m_Cost = cost;
	m_Points = points;
	m_Colour = colour;
}

int BuildingCard::getCost()
{
	return m_Cost;
}

CardColour BuildingCard::getColour()
{
	return m_Colour;
}
