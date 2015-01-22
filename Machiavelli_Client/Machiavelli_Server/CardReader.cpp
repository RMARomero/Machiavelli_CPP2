#include "CardReader.h"
#include <iostream>

CardReader::CardReader(string filePath)
{
	//maps to sort and keep track of content within the .csv file
	m_sFilePath = filePath;
	m_ColourMap["geel"] = yellow; //assign enum to string in map
	m_ColourMap["groen"] = green;
	m_ColourMap["blauw"] = blue;
	m_ColourMap["rood"] = red;
	m_ColourMap["lila"] = purple;

	m_CharacterMap["Assassin"] = Assassin;
	m_CharacterMap["Thief"] = Thief;
	m_CharacterMap["Magician"] = Magician;
	m_CharacterMap["King"] = King;
	m_CharacterMap["Bishop"] = Bishop;
	m_CharacterMap["Merchant"] = Merchant;
	m_CharacterMap["Architect"] = Architect;
	m_CharacterMap["Warlord"] = Warlord;
}

void CardReader::parse()
{
	ifstream input;
	input.exceptions(ifstream::failbit | ifstream::badbit);
	try {

		input.open(m_sFilePath);
		
		char delimeter = ';';
		string line;
		while (!input.eof()) // there is input overload classfile
		{
			getline(input, line, '\n');
			vector<string> result = split(line.c_str(), delimeter); //split the comma seperated entries into a vector of strings without the comma

			if (result.size() < 5) //check to see you are not going to construct a big card
				continue;

			string name = result.at(0);
			int costs = atoi(result.at(1).c_str());
			int points = atoi(result.at(1).c_str());
			string color = result.at(2);
			int amount = atoi(result.at(3).c_str());

			createCard(name, costs, points, color, amount, false);
		}


	}
	catch (ifstream::failure e) {
		std::cout << "\nException opening/reading file: " << e.what() << "\n";
	}
	input.close();
}

void CardReader::parseCharacters()
{
	ifstream input;
	input.exceptions(ifstream::failbit | ifstream::badbit);
	try {

		input.open(m_sFilePath);

		char delimeter = ';';
		string line;
		while (!input.eof()) // there is input overload classfile
		{
			getline(input, line, '\n');
			//for (string line; getline(input, line);) //loop until end of file
			//{
			vector<string> result = split(line.c_str(), delimeter); //split the comma seperated entries into a vector of strings without the comma

			if (result.size() < 2) //check to see you are not going to construct a big card
				continue;

			string name;

			if (result.at(1) == "Moordenaar")
			{
				name = "Assassin";
			}
			else if (result.at(1) == "Dief")
			{
				name = "Thief";
			}
			else if (result.at(1) == "Magiër")
			{
				name = "Magician";
			}
			else if (result.at(1) == "Koning")
			{
				name = "King";
			}
			else if (result.at(1) == "Prediker")
			{
				name = "Bishop";
			}
			else if (result.at(1) == "Koopman")
			{
				name = "Merchant";
			}
			else if (result.at(1) == "Bouwmeester")
			{
				name = "Architect";
			}
			else if (result.at(1) == "Condottiere")
			{
				name = "Warlord";
			}

			createCharCard(name);
		}
	}
	catch (ifstream::failure e) {
		std::cout << "\nException opening/reading file: " << e.what() << "\n";
	}
	input.close();


}

void CardReader::createCharCard(string name)
{
	shared_ptr < CharacterCard > newCard{ new CharacterCard(name, m_CharacterMap[name]) };
	m_CharCards.push_back(newCard);
}

void CardReader::createCard(string name, int costs, int points, string color, int amount, bool special)
{
	for (int i{ 0 }; i < amount; i++)
	{
		shared_ptr < BuildingCard > newCard{ new BuildingCard(name, costs, points, m_ColourMap[color]) };
		m_Cards.push_back(newCard);
	}
}

vector<string> CardReader::split(const char *str, char c)
{
	vector<string> result;

	do
	{
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(string(begin, str));
	} while (0 != *str++);

	//generates broken code
	/*while (0 != *str)
	{
	const char *begin = str;

	while (*str != c && *str)
	str++;

	result.push_back(string(begin, str));
	str++;
	}*/

	return result;
}