#include "GameManager.h"
#include <exception>
#include "LobbyState.h"
#include "FinishedState.h"
using std::exception;
using std::cerr;


GameManager::GameManager()
{
	m_PlayerListContainer = shared_ptr<PlayerList> {new PlayerList};
	m_CurrentGameState = unique_ptr<IGameState> {new LobbyState};
	m_CardManager = unique_ptr < CardManager > {new CardManager};
}



void GameManager::GameLoop()
{
	while (!IsGameFinished())
	{
		m_CurrentGameState->Handle(*this);
	}

	m_CurrentGameState = unique_ptr < IGameState > {new FinishedState};
}


void GameManager::SetGamestate(unique_ptr<IGameState> state){
	m_CurrentGameState = std::move(state);
}

void GameManager::MarkGameAsFinished(){
	m_IsFinished = true;
}

bool GameManager::IsGameFinished(){
	return m_IsFinished;
}




shared_ptr<PlayerList> GameManager::GetPlayerList(){
	return m_PlayerListContainer;
}
shared_ptr<CardManager> GameManager::GetCardManager(){
	return m_CardManager;
}

GameManager::~GameManager()
{
}
