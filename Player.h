#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Player
{
protected:
	int num; // 등록순 인덱스
    string name; // 플레이어 이름
    double balance; // 잔고
	double winingRate; // 승률

public:
	Player(int num, string name, double balance, double rate) : num(num), name(name), balance(balance), winingRate(rate)
	{}
	
	Player()
	{}
	~Player()
	{}

	int getNum() const
	{
		return num;
	}
	string getName() const
	{
		return name;
	}
	double getBalance() const
	{
		return balance;
	}
	double getRate() const
	{
		return winingRate;
	}
	
	void setBalance(double money)
	{
		balance += money;
	}
	
	void setPlayer()
	{}
	void showPlayerInfo()
	{
		cout<<"showPlayerInfo()"<<endl;
	}
};

class GamePlayer : public Player
{
protected:
	vector<Card> * Hand;
	double Starting_balance;
	double Bet;
	double Sum;
	
	double accMinus;
	double accPlus;
	
public:
	GamePlayer(int num, string name, double balance, double rate) : Player(num, name, balance, rate)
	{}
	GamePlayer() : Player()
	{}
	~GamePlayer()
	{}
	
	bool canBet()
	{
		return false;
	}
	
	void setBet()
	{}
	void setCards()
	{}
	void setStartingBalance()
	{}
	
	double getStartingBalance()
	{
		return 0;
	}
	double getAccMinus()
	{
		return 0;
	}
	double getAccPlus()
	{
		return 0;
	}
	
	
};

bool cmpNum(const Player &a, const Player &b){
	return a.getNum() < b.getNum();
}

class Dealer : public GamePlayer
{
public:
	
	
};
