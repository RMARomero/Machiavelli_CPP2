#include "FinishedState.h"
#include "GameManager.h"

FinishedState::FinishedState()
{
	/* Class that will calculate who won, send all the players some text with the winner, and points per player overview,
		then close all concetions with current players,
		(optional: take all player cards, reset decks, switch to lobby state)
	*/
}

void FinishedState::Handle(GameManager& gm)
{
	map<shared_ptr<Player>, int> scoreboard;
	
	for (int i{ 0 }; gm.GetPlayerList()->Size(); i++) 
	{
		int points{ 0 };
		shared_ptr<Player> player = gm.GetPlayerList()->GetPlayerAt(i);

		// Points for every building in the city
		points += player->GetCityCardContainer()->size();

		// 5 points if player owns buildings of all the 5 colours
		if (HasBuildingsOf5Colours(player)) {
			points += 5;
		}
		// 4 points for the first player who builds 8 buildings
		if (player.get() == gm.get8Buildings().get()) {
			points += 4;
		}
		// 2 points for each player who constructed 8 buildings as well
		else if (player->GetCityCardContainer()->size() >= 8) {
			points += 2;
		}

		if (player->GetCityCardContainer()->HasCard("Drakenpoort")) {
			points += 2;
		}

		if (player->GetCityCardContainer()->HasCard("Universiteit")) {
			points += 2;
		}

		scoreboard[player] = points;
	}

	shared_ptr<Player> winner = GetWinningPlayer(scoreboard);

	winner->Send("Congratulations, you have won the game with " + std::to_string(scoreboard[winner]) + " points");
	gm.GetPlayerList()->SendAllBut(winner, "The game has been won by " + winner->GetName() + " with " + std::to_string(scoreboard[winner]) + " points");

	while (true)
	{
		// prevent the server from shutting down.
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


bool FinishedState::HasBuildingsOf5Colours(shared_ptr<Player> player)
{
	vector<CardColour> checkList;
	
	for (int i{ 0 }; i < player->GetCityCardContainer()->size(); i++)
	{
		shared_ptr<DistrictCard> card = player->GetCityCardContainer()->at(i);

		if (std::find(checkList.begin(), checkList.end(), card->getColour()) != checkList.end())
		{
			checkList.push_back(card->getColour());
		}
	}

	return checkList.size() >= 5 || checkList.size() >= 4 && player->GetCityCardContainer()->HasCard("Hof der Wonderen");
}

shared_ptr<Player> FinishedState::GetWinningPlayer(map<shared_ptr<Player>, int> scoreboard)
{
	int highestScore = -1;
	shared_ptr<Player> winner;

	for (auto &score : scoreboard)
	{
		if (score.second > highestScore)
		{
			highestScore = score.second;
			winner = score.first;
		}
		else if (score.second == highestScore)
		{
			if (score.first->GetCityCardContainer()->size() > winner->GetCityCardContainer()->size())
			{
				winner = score.first;
			}
		}
	}

	return winner;
}