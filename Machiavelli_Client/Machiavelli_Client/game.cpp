#include "game.h"

#include "stdafx.h"
#include "Socket.h"
#include <iostream>
#include <fstream>
#include <string>

#include <thread>
#include <exception>
#include <memory>

using namespace std;

game::game()
{
	storeServerInformation();

	shared_ptr<ClientSocket> server{ new ClientSocket(m_IP, m_Portnumber) }; //we can pass some string literals and numbers here, but no

	while (true)
	{
		try
		{
			string cmd = server->readline(); //read first line

			if (cmd == "Bye!")
			{
				server->close();
				//break; //break the game loop, and end the connection
			}
			else if (cmd == "input")
			{
				string input = "";
				getline(cin, input);
				server->write(input + "\n"); //write the input and pass it on to the server
			}
			else
			{
				cerr << cmd << '\n';
			}
		}
		catch (const exception& ex)
		{
			//error happend here
		}
		catch (...)
		{
			//error happend here
		}
	}

}

game::~game()
{
	delete[] m_IP;
}

void game::storeServerInformation()
{

	std::string ip;
	const string textfile{ "config.txt" };
	ifstream input_file; //read file and extract ip/port etc.
	input_file.exceptions(ifstream::failbit | ifstream::badbit);
	try {

		input_file.open(textfile);
		if (input_file.is_open())
		{
			input_file >> ip;
			input_file >> m_Portnumber;
			m_IP = &ip[0];
		}
	}
	catch (ifstream::failure e) {
		std::cout << "\nException opening/reading file: " << e.what() << "\n";
	}
	input_file.close();

}


