#include "SocketManager.h"
#include "InputManager.h"

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "GameManager.h"

#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <memory>

//#include "SyncedQueue.h"

using namespace std;

SocketManager& SocketManager::getInstance()
{
	static SocketManager instance;
	return instance;
}

void Start_GameLoop(shared_ptr<GameManager> gm)
{
	gm->GameLoop();
}

void handle_client(Socket* socket, shared_ptr<GameManager> gm) // this function runs in a separate thread
{
	shared_ptr<Socket> client{ socket };
	shared_ptr<Player> player{ new Player(client) };

	// Recieve players and ask for their names
	player->Send("Welcome to the Machiavelli! Please enter your name?\n");
	player->AllowInput();
	string name = client->readline();

	/* TODO: */
	// Check if the game is already in progress...
	//If in progress:
	/* Tell the player he missed the train... return method (and thus end thread and close connection) */
	
	//If not in progress:
	player->Send("\nLet's wait until all players are ready! To quit, type 'quit'.\n");
	player->SetName(name);

	gm->GetPlayerList()->InsertPlayer(player);

	while (true) { // game loop
		try {
			// read first line of request
			string cmd = client->readline();
			cerr << "client (" << client->get() << ") said: " << cmd << '\n';

			if (cmd == "quit") {
				player->Send("Bye!\n");
				//client->write(socketexample::prompt);
				break; // out of game loop, will end this thread and close connection
			}

			ClientCommand command{ cmd, player, client };
			SocketManager::getInstance().queue.put(command);

		}
		catch (const exception& ex) {
			player->Send("ERROR: ");
			player->Send(ex.what());
			player->Send("\n");
		}
		catch (...) {
			player->Send("ERROR: something went wrong during handling of your request. Sorry!\n");
		}
	}
}

void SocketManager::getServerInformation()
{
	std::string ip;
	const string textfile("config.txt");
	// input file stream, opent textfile voor lezen
	ifstream input_file(textfile);
	input_file >> m_iPort;

}

void SocketManager::start()
{
	getServerInformation();

	std::shared_ptr < GameManager > gm{ new GameManager };

	// start command consumer thread
	thread consumer{ Start_GameLoop, gm };
	consumer.detach(); // detaching is usually ugly, but in this case the right thing to do

	// create a server socket
	ServerSocket server(m_iPort);

	while (true) {
		try {
			// wait for connection from client; will create new socket
			cerr << "server listening" << '\n';
			Socket* client = nullptr;

			while ((client = server.accept()) != nullptr) 
			{
				// communicate with client over new socket in separate thread
				thread handler{ handle_client, client, gm };
				handler.detach(); // detaching is usually ugly, but in this case the right thing to do
				cerr << "server listening again" << '\n';
			}
		}
		catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
		}
	}
}