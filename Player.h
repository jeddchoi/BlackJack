#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Player
{
protected:
	int num;
    string name;
    int balance;
	double winingRate;

public:
	Player(int num, string name, int balance, double rate) : num(num), name(name), balance(balance), winingRate(rate)
	{}
	
	~Player();

	int getNum() const
	{
		return num;
	}
	string getName() const
	{
		return name;
	}
	int getBalance() const
	{
		return balance;
	}
	int getRate() const
	{
		return winingRate;
	}
	
	void setBalance();
	
	void setPlayer();
	void showPlayerInfo();
};

class GamePlayer : public Player
{
protected:
	vector<Card> * Hand;
	int Starting_balance;
	int Bet;
	int Sum;
	
	int accMinus;
	int accPlus;
	
public:
	GamePlayer();
	~GamePlayer();
	
	bool canBet();
	
	void setBet();
	void setCards();
	void setStartingBalance();
	
	int getStartingBalance();
	int getAccMinus();
	int getAccPlus();
	
	
};

bool cmpNum(const Player &a, const Player &b){
	return a.getNum() < b.getNum();
}
class Dealer : public GamePlayer
{
public:
	
	
};
