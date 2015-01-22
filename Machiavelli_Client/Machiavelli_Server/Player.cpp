#include "Player.h"
//#include "SyncedQueue.h"
#include <exception>
#include "SocketManager.h"
using std::exception;

bool Player::HasCharacterCard(eCharacterCard role)
{
	bool found = false;
	for (int i = 0; i < m_CharacterCards->size() && !found; i++)
	{
		found = m_CharacterCards->GetCardDeck().at(i)->GetEnum() == role;
	}
	return found;
}

bool Player::ValidateAnswer(string input, vector<string> expectedAnswers)
{
	try {
		int position = stoi(input);
		return position >= 0 && position < expectedAnswers.size();
	}
	catch (...) {
		return false;
	}

}

string Player::RequestInput(string question)
{
	AllowInput();
	return GetPlayerInput();
}

int Player::RequestInput(string question, vector<string> expectedAnswers)
{
	string output = question.append("\n");
	for (int i = 0; i < expectedAnswers.size(); i++){
		output.append(" [");
		output.append(std::to_string(i));
		output.append("] ");
		output.append(expectedAnswers.at(i));
		output.append("\n");
	}
	
	string answer = "";
	do{
		Send(output);
		AllowInput();
		answer = GetPlayerInput();
	} while (!ValidateAnswer(answer, expectedAnswers));

	return stoi(answer);
}

string Player::GetPlayerInput()
{
	while (true) {
		ClientCommand command;
		SocketManager::getInstance().queue.get(command); // will block here unless there still are command objects in the queue
		shared_ptr<Socket> client{ command.get_client() };
		if (client) {
			try {
				if (command.getPlayer().get() == this){

					return command.get_cmd();
				}
			}
			catch (const exception& ex) {
				client->write("Sorry, ");
				client->write(ex.what());
				client->write("\n");
			}
			catch (...) {
				client->write("Sorry, something went wrong during handling of your request.\n");
			}
		}
		else {
			std::cerr << "trying to handle command for client who has disappeared...\n";
		}
	}
}

void Player::GiveGPForCards(CardColour colour)
{
	int cardCount{ 0 };

	for (int i{ 0 }; i < GetCityCardContainer()->size(); i++)
	{
		if (GetCityCardContainer()->at(i)->getColour() == colour)
		{
			cardCount++;
		}
	}

	if (GetCityCardContainer()->HasCard("School voor magiers"))
	{
		cardCount++;
	}

	if (cardCount > 0)
	{
		Send("You have received additional gold because of the buildings in your city! Bonus gold: " + std::to_string(cardCount));
		GiveGoldPieces(cardCount);

	}
}

void Player::ShowStats()
{
	string output = "\n";
	output += " == Information ==\n";

	output += "Your city's information:\n";

	for (int i{ 0 }; i < GetCityCardContainer()->size(); i++) {
		output += " - " + GetCityCardContainer()->at(i)->getName() + "\n";
	}

	output += "\n\n Your BuildingCards: \n";

	for (int i{ 0 }; i < GetBuildingCardContainer()->size(); i++) {
		output += " - " + GetBuildingCardContainer()->at(i)->getName() + "\n";
	}

	output += "\n\n Your Characters:\n";

	for (int i{ 0 }; i < GetCharacterCardContainer()->size(); i++) {
		output += " - " + GetCharacterCardContainer()->at(i)->getName() + "\n";
	}

	output += "\n\n You currently have: " + std::to_string(GetGoldPieces()) + " gold\n";

	Send(output);
}

