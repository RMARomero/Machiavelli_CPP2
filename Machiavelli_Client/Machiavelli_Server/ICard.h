#pragma once

#include <string>
using std::string;

class ICard
{
protected:
	string m_Name;
public:
	ICard();
	string GetName();
	virtual ~ICard();
};

