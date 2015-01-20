#include "LobbyState.h"
#include "GameManager.h"
#include "GameRunningState.h"

#include <chrono>
#include <thread>

void LobbyState::Handle(GameManager& gm)
{
	while (gm.GetPlayerList()->Size() < 2)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	gm.SetGamestate(unique_ptr<IGameState> { new GameRunningState });
}
