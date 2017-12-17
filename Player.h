#pragma once
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;

class Player
{
protected:
	int num; // 등록순 인덱스
	string name; // 플레이어 이름
	double balance; // 잔고
	
public:
	Player(int num, string name, double balance);
	
	Player();
	~Player();
	
	int getNum() const;
	string getName() const;
	double getBalance() const;
	
	void setBalance(double money);
	
	void setPlayer(Player who);
	void showPlayerInfo();
};

bool cmpNum(const Player &a, const Player &b);

bool cmpBalance(const Player &a, const Player &b);

class GamePlayer : public Player
{
protected:
	vector<Card> Hand;
	double Starting_balance;
	double Bet;
	double Sum;
	double insurance;
	
	
public:
	GamePlayer(int num, string name, double balance);
	GamePlayer() ;
	~GamePlayer();
	
	bool canBet(int money);
	
	
	double getBet();
	
	void setInsurance(double insurance);
	
	double getInsurance();
	
	void plusBet(int money);
	
	void setStartingBalance();
	
	double getStartingBalance();
	
	void drawTwoCards(Deck &deck);
	
	void drawACard(Deck &deck);
	
	void showFirstTwoCards();
	
	double getCardSum();
	
	void initGame();
	
	bool isFirstCardsBJ();
	
	void showHand();
};

// 딜러 카드의 합과 플레이어 카드의 합 비교
bool operator>(GamePlayer& p1, GamePlayer& p2);

bool operator==(GamePlayer& p1, GamePlayer& p2);

class Dealer : public GamePlayer
{
public:
	
	void showOpenCard();
	
	bool isOpenCardAce();
	
	void showHand();
};
