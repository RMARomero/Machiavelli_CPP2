#pragma once

#include <memory>
#include <vector>

#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand

#include "ICard.h"

using std::shared_ptr;
using std::vector;

template<class T>
class CardPile
{
private:
	vector<shared_ptr<T>> m_Cards;
public:
	CardPile(){}

	shared_ptr<T> At(int position){
		shared_ptr<T> card{ nullptr };
		card = m_Cards.at(position);

		return card;
	}

	shared_ptr<T> Pop(){
		shared_ptr<T> card{ nullptr };
		if (!m_Cards.empty()){
			card = m_Cards.back();
			m_Cards.pop_back();
		}
		return card;
	}
	shared_ptr<T> Peek(){
		shared_ptr<T> card{ nullptr };
		if (!m_Cards.empty()){
			card = m_Cards.back();
		}
		return card;
	}

	shared_ptr<T> Take(int position){
		shared_ptr<T> card{ nullptr };
		card = m_Cards.at(position);
		m_Cards.erase(m_Cards.begin() + position);
		return card;
	}

	void Shuffle(){
		std::random_shuffle(m_Cards.begin(), m_Cards.end());
	}

	void Push_Back(shared_ptr<T> card){
		m_Cards.push_back(card);
	}

	int Size(){
		return m_Cards.size();
	}

	vector<shared_ptr<T>> GetCardPile(){
		return m_Cards;
	}
	vector<shared_ptr<T>> TakeCardPile() {
		vector<shared_ptr<T>> tmp = m_Cards;
		m_Cards.clear();
		return tmp;
	}
	void AddCardPile(vector<shared_ptr<T>> pile) {
		m_Cards = pile;
	}

	virtual ~CardPile() {}

	bool HasCard(string name) {
		bool result = false;
		for (int i{ 0 }; i < m_Cards.size() && !result; i++) {
			result = (m_Cards.at(i)->GetName() == name);
		}

		return result;
	}

	vector<string> ToVector() {
		vector<string> cardNames;

		for (int i{ 0 }; i < m_Cards.size(); i++) {
			cardNames.push_back(m_Cards.at(i)->GetName());
		}

		return cardNames;
	
	}
};

/*
template<>
class CardPile <ICard>
{
private:
	vector<shared_ptr<ICard>> cards;
public:

	int AmountOf(std::string name){
		int result = 0;
		for (int i = 0; i < cards.size(); i++){
			if (cards.at(i)->GetName() == name) result++;
		}
		return result;
	}
	
};

*/