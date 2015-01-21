#pragma once

#include <string>
#include "Socket.h"
#include <memory>
#include <vector>

#include "CardDeck.h"
#include "CharacterCard.h"
#include "DistrictCard.h"

using std::vector;
using std::shared_ptr;
using std::string;


class Player
{
public:
	Player(shared_ptr<Socket> socket);
	virtual ~Player(){}

	shared_ptr<CardDeck<CharacterCard>> GetCharacterCardContainer();
	shared_ptr<CardDeck<DistrictCard>> GetDistrictCardContainer();
	shared_ptr<CardDeck<DistrictCard>> GetCityCardContainer();
	bool HasCharacterCard(eCharacterCard role);

	string GetName();
	void SetName(string name);
	void Send(string Message);
	void AllowInput();

	string RequestInput(string question);
	int RequestInput(string question, vector<string> expectedAnswers);
	string GetPlayerInput();

	void GiveGoldPieces(int amount);

	int GetGoldPieces();
	void SetGoldPieces(int amount);

	void GiveGPForCards(CardColour colour);
	void ShowStats();
private:
	string m_Name;
	int m_GoldPieces{ 0 };
	shared_ptr<Socket> m_Socket;
	shared_ptr<CardDeck<CharacterCard>> m_CharacterCards = shared_ptr<CardDeck<CharacterCard>> { new CardDeck<CharacterCard> };
	shared_ptr<CardDeck<DistrictCard>> m_DistrictCards = shared_ptr<CardDeck<DistrictCard>> { new CardDeck<DistrictCard> };
	shared_ptr<CardDeck<DistrictCard>> m_City = shared_ptr<CardDeck<DistrictCard>> { new CardDeck<DistrictCard> };

	bool ValidateAnswer(string input, vector<string> expectedAnswers);

};

