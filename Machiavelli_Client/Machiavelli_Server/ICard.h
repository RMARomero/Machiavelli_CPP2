#pragma once

#include <string>

using std::string;

class ICard
{
public:
	ICard();
	virtual ~ICard();
	string getName();
protected:
	string m_Name;
};

