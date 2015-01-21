#include "GameManager.h"
#include <exception>
#include "LobbyState.h"
#include "FinishedState.h"

using std::exception;

GameManager::GameManager()
{
	m_PlayerListContainer = shared_ptr<PlayerList> {new PlayerList};
	m_CurrentGameState = unique_ptr<IGameState> {new LobbyState};
	m_CardManager = unique_ptr <CardManager> {new CardManager};
}

void GameManager::GameLoop()
{
	while (!IsGameFinished())
	{
		m_CurrentGameState->Handle(*this);
	}
	m_CurrentGameState = unique_ptr<IGameState> {new FinishedState};
}
