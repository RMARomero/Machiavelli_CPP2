#include "CardReader.h"

CardReader::CardReader(string filePath) {
	m_FilePath = filePath;
	m_ColourMap["geel"] = yellow;
	m_ColourMap["groen"] = green;
	m_ColourMap["blauw"] = yellow;
	m_ColourMap["rood"] = red;
	m_ColourMap["lila"] = purple;
}

void CardReader::parse() {
	ifstream input(m_FilePath);

	for (string line; getline(input, line);) {
		vector<string> result = split(line.c_str());

		if (result.size() <5) {
			continue;
		}

		string name = result.at(0);
		int costs = atoi(result.at(1).c_str());
		int points = atoi(result.at(1).c_str());
		string color = result.at(2);
		int amount = atoi(result.at(3).c_str());

		constructCard(name, costs, points, color, amount);

	}
}

void CardReader::constructCard(string name, int costs, int points, string color, int amount) {
	for (int i{ 0 }; i < amount; i++) {
		shared_ptr < DistrictCard > newCard { new DistrictCard(name, costs, points, m_ColourMap[color])};
		m_Cards.push_back(newCard);
	}

}

vector<shared_ptr<DistrictCard>> CardReader::getCards() {

	return m_Cards;
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

	return result;
}