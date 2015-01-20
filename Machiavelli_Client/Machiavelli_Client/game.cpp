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
				break; //not sure if you ever come here.
			}
			else if (cmd == "input")
			{
				string input = "";
				getline(cin, input);
				server->write(input + "\n"); //not sure if you ever come here
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
	/*m_IP = "127.1.0.0";
	m_Portnumber = 8765;*/
	std::string ip;
	const string textfile("config.txt");
	ifstream input_file(textfile); //read file and extract ip/port etc.
	if (input_file.is_open())
	{
		input_file >> ip;
		input_file >> m_Portnumber;
		m_IP = &ip[0];
		input_file.close();
	}
}


