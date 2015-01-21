#pragma once
#include "Player.h"
#include <memory>
#include <vector>

using std::vector;
using std::string;
using std::shared_ptr;


class PlayerList
{
public:
	PlayerList();
	virtual ~PlayerList();

	shared_ptr<Player> GetPlayerAt(int position);
	shared_ptr<Player> GetPlayerByRole(eCharacterCard card);
	shared_ptr<Player> GetPlayerByName(string name);

	void InsertPlayer(shared_ptr<Player> player) { m_PlayerList.push_back(player); }
	void RemovePlayer(shared_ptr<Player> player);
	void SendAll(string message);
	void SendAllBut(shared_ptr<Player> player, string message);
	void MoveToFront(shared_ptr<Player> player);

	int Size(){	return m_PlayerList.size(); }
private:
	vector<shared_ptr<Player>> m_PlayerList;
	vector<shared_ptr<int>> m_Temp;
};
