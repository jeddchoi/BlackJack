#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

namespace CARD
{
	const int CARDNUMBER = 52;
	/* 1또는 10으로 계산할 수 있는 A */
	const int DI_A = 1;
	const int SD_A = 2;
	const int HE_A = 3;
	const int CV_A = 4;
	
	/* 2 ~ 9 */
	const int DI_2 = 12;
	const int DI_3 = 13;
	const int DI_4 = 14;
	const int DI_5 = 15;
	const int DI_6 = 16;
	const int DI_7 = 17;
	const int DI_8 = 18;
	const int DI_9 = 19;
	
	const int SD_2 = 22;
	const int SD_3 = 23;
	const int SD_4 = 24;
	const int SD_5 = 25;
	const int SD_6 = 26;
	const int SD_7 = 27;
	const int SD_8 = 28;
	const int SD_9 = 29;
	
	const int HE_2 = 32;
	const int HE_3 = 33;
	const int HE_4 = 34;
	const int HE_5 = 35;
	const int HE_6 = 36;
	const int HE_7 = 37;
	const int HE_8 = 38;
	const int HE_9 = 39;
	
	const int CV_2 = 42;
	const int CV_3 = 43;
	const int CV_4 = 44;
	const int CV_5 = 45;
	const int CV_6 = 46;
	const int CV_7 = 47;
	const int CV_8 = 48;
	const int CV_9 = 49;
	
	/* 10으로 계산되는 10, K, J, Q */
	const int DI_10 = 100;
	const int DI_K = 110;
	const int DI_J = 120;
	const int DI_Q = 130;
	
	const int SD_10 = 200;
	const int SD_K = 210;
	const int SD_J = 220;
	const int SD_Q = 230;
	
	const int HE_10 = 300;
	const int HE_K = 310;
	const int HE_J = 320;
	const int HE_Q = 330;
	
	const int CV_10 = 400;
	const int CV_K = 410;
	const int CV_J = 420;
	const int CV_Q = 430;
	
}

class Card
{
protected:
	int value; // 실제로 적용되는 값
	
private:
	int cards;
	
public:
	int shp, number, cardName;
	Card() { cards = 52; }
	~Card() {};
	
	void setCard(int cardName) {
		setShape(cardName);
		setValue(cardName);
		setNumber(cardName);
	}
	
	void setShape(int cardName) {
		if (cardName < 10)
			shp = cardName;
		else if (10 < cardName && cardName < 50)
			shp = cardName / 10;
		else if (50 < cardName) {
			shp = cardName / 100;
		}
	}
	
	void setValue(int cardName) {
		if (cardName < 10)
			value = 11;                     // A를 무조건 11로 처리
		else if (10 < cardName && cardName < 50)
			value = cardName % 10;
		else if (50 < cardName)
			value = 10;
	}
	
	void setNumber(int cardName) {
		if (cardName < 10)
			number = 'A';  //65
		else if (10 < cardName && cardName < 50)
			number = cardName % 10;
		else if (50 < cardName) {
			if (cardName % 100 == 0)
				number = 10;
			else if (cardName % 100 == 10)
				number = 'K'; //75
			else if (cardName % 100 == 20)
				number = 'J'; //74
			else if (cardName % 100 == 30)
				number = 'Q'; //81
		}
	}
	
	char getShape() {
		char shape;
		
		if (shp == 1)
			shape = 'D';
		else if (shp == 2)
			shape = 'S';
		else if (shp == 3)
			shape = 'H';
		else if (shp == 4)
			shape = 'C';
		
		return shape;
	}
	
	int getNumber() {
		return number;
	}
	
	int getValue() {
		return value;
	}
};

class Deck
{
	vector<Card> cards;
public:
	Deck() {
		cards.reserve(52);
		init();
	}
	~Deck() {};
	
	void shuffleDeck() {
		Card temp;
		int left;
		int right;
		
		for (int i = 0; i < 100; i++) {
			srand(time(NULL));
			left = rand() % CARD::CARDNUMBER;
			right = rand() % CARD::CARDNUMBER;
			temp = cards[left];
			cards[left] = cards[right];
			cards[right] = temp;
		}
	}
	
	int getRemainCardsNum() {
		return cards.size();
	}
	
	
	Card getACard() {
		Card card;
		char shape;
		if (cards.size() >= 1) {
			card = cards[cards.size() - 1];
			cards.pop_back();
			card.Card::setCard(card.cardName);
		}
		else {
			cout << "There is no cards." << endl;
			exit(-1);
		}
		return card;
	}
	
	void init() {
		Card new_card;
		int arr[52] = { 1, 2, 3, 4, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45, 46, 47, 48, 49, 100, 110, 120, 130, 200, 210, 220, 230, 300, 310, 320, 330, 400, 410, 420, 430 };
		cards.clear();
		for (int i = 0; i < 52; i++) {
			new_card.cardName = arr[i];
			cards.push_back(new_card);
		}
	}
};


int getSum(vector <Card> &Hand) {
	int num, sum = 0;
	if (Hand.empty())
		return 0;
	
	num = Hand.size();
	for (int i = 0; i < num; i++) {
		sum += Hand[i].getValue();
	}
	return sum;
}
