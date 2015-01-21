#pragma once

#include <string>
#include "Socket.h"
#include <memory>
#include <vector>

#include "CardDeck.h"
#include "CharacterCard.h"
#include "BuildingCard.h"

using std::vector;
using std::shared_ptr;
using std::string;


class Player
{
public:
	Player(shared_ptr<Socket> socket) : m_Socket{ socket }{}
	virtual ~Player(){}

	shared_ptr<CardDeck<CharacterCard>> GetCharacterCardContainer(){ return m_CharacterCards; }
	shared_ptr<CardDeck<BuildingCard>> GetBuildingCardContainer(){ return m_BuildingCards; }
	shared_ptr<CardDeck<BuildingCard>> GetCityCardContainer(){ return m_City; }

	string GetName(){ return m_Name; }
	void SetName(string name) { m_Name = name; }

	void Send(string message){	m_Socket->write(message + "\n"); }
	void AllowInput(){	m_Socket->write(GET_PLAYER_INPUT); }

	void GiveGoldPieces(int amount){ m_GoldPieces += amount; }
	void SetGoldPieces(int amount){ m_GoldPieces = amount; }
	int GetGoldPieces(){ return m_GoldPieces; }

	string RequestInput(string question);
	int RequestInput(string question, vector<string> expectedAnswers);
	string GetPlayerInput();

	bool HasCharacterCard(eCharacterCard role);
	void GiveGPForCards(CardColour colour);
	void ShowStats();

private:
	string m_Name;
	int m_GoldPieces{ 0 };
	shared_ptr<Socket> m_Socket;
	shared_ptr<CardDeck<CharacterCard>> m_CharacterCards = shared_ptr<CardDeck<CharacterCard>> { new CardDeck<CharacterCard> };
	shared_ptr<CardDeck<BuildingCard>> m_BuildingCards = shared_ptr<CardDeck<BuildingCard>> { new CardDeck<BuildingCard> };
	shared_ptr<CardDeck<BuildingCard>> m_City = shared_ptr<CardDeck<BuildingCard>> { new CardDeck<BuildingCard> };

	bool ValidateAnswer(string input, vector<string> expectedAnswers);

};

