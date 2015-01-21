#include "BuildingCard.h"
#include "CharacterCard.h"
#include <fstream>
#include <map>
#include <vector>
#include <memory>

using std::shared_ptr;
using std::vector;
using std::ifstream;
using std::map;

class CardReader 
{
public:
	CardReader(string filePath);
	virtual ~CardReader() {}

	void parse();
	void parseCharacters();

	void setFilePath(string filePath) { m_sFilePath = filePath; }
	vector<shared_ptr<BuildingCard>> getCards() { return m_Cards; }
	vector<shared_ptr<CharacterCard>> getCharCards() { return m_CharCards; }

private:
	string m_sFilePath;

	vector<shared_ptr<BuildingCard>> m_Cards;
	vector<shared_ptr<CharacterCard>> m_CharCards;
	map<string, CardColour> m_ColourMap;
	map<string, eCharacterCard> m_CharacterMap;

	vector<string> split(const char *str, char c);

	void createCharCard(string name);
	void createCard(string name, int costs, int points, string color, int amount, bool special);
};