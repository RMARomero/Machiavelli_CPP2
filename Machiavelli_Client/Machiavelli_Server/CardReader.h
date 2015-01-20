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
	virtual ~CardReader();

	void parse();
	vector<shared_ptr<DistrictCard>> getCards();
private:
	vector<shared_ptr<DistrictCard>> m_Cards;
	map<string, CardColour> m_ColourMap;

	string m_FilePath;

	void createCard(string name, int costs, int points, string color, int amount, bool special);
	vector<string> split(const char *str, char c);
	
};