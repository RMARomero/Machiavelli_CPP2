#pragma once

#include <string>
#include "Socket.h"
#include <memory>
#include <vector>

#include "CardPile.h"
#include "CharacterCard.h"
#include "DistrictCard.h"

using std::vector;
using std::shared_ptr;
using std::string;


class Player
{
private:
	string m_Name;
	int m_GoldPieces{ 0 };
	shared_ptr<Socket> m_Socket;
	shared_ptr<CardPile<CharacterCard>> m_CharacterCards = shared_ptr<CardPile<CharacterCard>> { new CardPile<CharacterCard> };
	shared_ptr<CardPile<DistrictCard>> m_DistrictCards = shared_ptr<CardPile<DistrictCard>> { new CardPile<DistrictCard> };
	shared_ptr<CardPile<DistrictCard>> m_City = shared_ptr<CardPile<DistrictCard>> { new CardPile<DistrictCard> };

	bool ValidateAnswer(string input, vector<string> expectedAnswers);

public:
	Player(shared_ptr<Socket> socket);

	shared_ptr<CardPile<CharacterCard>> GetCharacterCardContainer();
	shared_ptr<CardPile<DistrictCard>> GetDistrictCardContainer();
	shared_ptr<CardPile<DistrictCard>> GetCityCardContainer();
	bool HasCharacterCard(eCharacterCard role);

	string GetName();
	void SetName(string name);
	void Send(string Message);
	void AllowInput();

	string RequestInput(string question);
	int RequestInput(string question, vector<string> expectedAnswers);
	string GetPlayerInput();

	virtual ~Player();

	void GiveGoldPieces(int amount);

	int GetGoldPieces();
	void SetGoldPieces(int amount);

	void GiveGPForCards(CardColour colour);
	void ShowStats();
};

