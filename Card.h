#ifndef __CARD_H_
#define __CARD_H_

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
	int cardName; // 카드 이름
	int value; // 실제로 적용되는 값

private:
	char shp;
	int cards, number;

public:
	Card(int cards);
	Card(){cards = 52;}
	~Card();
	
	void setCard(char shape, int number);
	void setShape(char shape);
	void setValue(int number);
	
	char getShape(int shp);
	int getNumber();
	int getValue();
	
};

class Deck
{
	vector<Card> cards;
public:
	// 52장으로 이루어져 있는 카드 생성하기
	Deck();
	~Deck();
	
	// 덱 카드 순서 섞기
	void shuffleDeck();

	// 덱에 남아있는 카드 갯수 반환하기
	int getRemainCardsNum();
	
	// 덱에서 맨 위에(뒤에) 있는 카드 뽑기
	Card getACard();	
	
	void init();
};

#endif /*__CARD_H_*/
