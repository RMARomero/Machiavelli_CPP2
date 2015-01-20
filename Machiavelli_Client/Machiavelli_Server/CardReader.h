#include "DistrictCard.h"
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
	vector<shared_ptr<DistrictCard>> getCards() { return m_Cards; }

private:
	string m_sFilePath;

	vector<shared_ptr<DistrictCard>> m_Cards;
	map<string, CardColour> m_ColourMap;

	vector<string> split(const char *str, char c);

	void createCard(string name, int costs, int points, string color, int amount, bool special);
};