#pragma once

#include <memory>
#include <vector>

#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand

#include "ICard.h"

using std::shared_ptr;
using std::vector;

template<class T>
class CardDeck
{
private:
	vector<shared_ptr<T>> m_Cards;
public:
	CardDeck(){}
	virtual ~CardDeck() {}

	shared_ptr<T> at(int position)
	{
		shared_ptr<T> card{ nullptr };
		card = m_Cards.at(position);

		return card;
	}

	shared_ptr<T> pop_back()
	{
		shared_ptr<T> card{ nullptr };
		if (!m_Cards.empty())
		{
			card = m_Cards.back();
			m_Cards.pop_back();
		}
		return card;
	}

	shared_ptr<T> peek()
	{
		shared_ptr<T> card{ nullptr };
		if (!m_Cards.empty())
		{
			card = m_Cards.back();
		}
		return card;
	}

	shared_ptr<T> take(int position)
	{
		shared_ptr<T> card{ nullptr };
		card = m_Cards.at(position);
		m_Cards.erase(m_Cards.begin() + position);
		return card;
	}

	void shuffle(){ std::random_shuffle(m_Cards.begin(), m_Cards.end()); }

	void push_back(shared_ptr<T> card){ m_Cards.push_back(card); }

	int size(){	return m_Cards.size();	}

	vector<shared_ptr<T>> GetCardDeck(){ return m_Cards; }

	vector<shared_ptr<T>> TakeCardDeck()
	{
		vector<shared_ptr<T>> tmp = m_Cards;
		m_Cards.clear();
		return tmp;
	}

	void AddCardDeck(vector<shared_ptr<T>> pile) {	m_Cards = pile;	}

	bool HasCard(string name) 
	{
		bool result = false;
		for (int i{ 0 }; i < m_Cards.size() && !result; i++) 
		{
			result = (m_Cards.at(i)->getName() == name);
		}

		return result;
	}

	vector<string> to_vector() 
	{
		vector<string> cardNames;
		for (int i{ 0 }; i < m_Cards.size(); i++) 
		{
			cardNames.push_back(m_Cards.at(i)->getName());
		}
		return cardNames;
	}
};
