#pragma once
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "PlayerList.h"
#include "IGameState.h"
#include "CardManager.h"
#include "ICard.h"
using std::unique_ptr;

class GameManager
{
private:
	shared_ptr<PlayerList> m_PlayerListContainer;
	unique_ptr<IGameState> m_CurrentGameState;
	shared_ptr<CardManager> m_CardManager;
	bool m_IsFinished{false};

	eCharacterCard m_KilledCharacter;
	eCharacterCard m_RobbedCharacter;
	shared_ptr<Player> m_8Buildings;
public:
	GameManager();

	void GameLoop();

	void SetGamestate(unique_ptr<IGameState> state);
	shared_ptr<PlayerList> GetPlayerList();
	shared_ptr<CardManager> GetCardManager();

	void MarkGameAsFinished();
	bool IsGameFinished();

	bool isRobbed(eCharacterCard character) { return m_RobbedCharacter == character; }
	bool isKilled(eCharacterCard character) { return m_KilledCharacter == character; }

	void setKilled(eCharacterCard character) { m_KilledCharacter = character; }
	void setRobbed(eCharacterCard character) { m_RobbedCharacter = character; }

	void set8Buildings(shared_ptr<Player> player) { m_8Buildings = player;  }
	shared_ptr<Player> get8Buildings() { return m_8Buildings;  }

	~GameManager();
};

