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
public:
	GameManager();
	~GameManager(){}

	void GameLoop();

	void SetGamestate(unique_ptr<IGameState> state){ m_CurrentGameState = std::move(state);	}

	shared_ptr<PlayerList> GetPlayerList(){	return m_PlayerListContainer; }
	shared_ptr<CardManager> GetCardManager(){ return m_CardManager; }

	void FinishGame() { m_bIsFinished = true; }
	bool IsGameFinished() { return m_bIsFinished; }

	bool isRobbed(eCharacterCard character) { return m_eRobbedCharacter == character; }
	bool isKilled(eCharacterCard character) { return m_eKilledCharacter == character; }
	void setKilled(eCharacterCard character) { m_eKilledCharacter = character; }
	void setRobbed(eCharacterCard character) { m_eRobbedCharacter = character; }
	void set8Buildings(shared_ptr<Player> player) { m_8Buildings = player;  }
	shared_ptr<Player> get8Buildings() { return m_8Buildings;  }

private:
	shared_ptr<PlayerList> m_PlayerListContainer;
	unique_ptr<IGameState> m_CurrentGameState;
	shared_ptr<CardManager> m_CardManager;
	bool m_bIsFinished{ false };

	eCharacterCard m_eKilledCharacter;
	eCharacterCard m_eRobbedCharacter;
	shared_ptr<Player> m_8Buildings;
};

