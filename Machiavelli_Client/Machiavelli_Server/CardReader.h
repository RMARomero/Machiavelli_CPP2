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
	~CardReader();

	void parse();
	vector<shared_ptr<DistrictCard>> getCards();
private:
	vector<shared_ptr<DistrictCard>> m_Cards;
	string m_FilePath;
	map<string, CardColour> m_ColourMap;


	vector<string> split(const char *str, char c = ';');
	void constructCard(string name, int costs, int points, string color, int amount);
};