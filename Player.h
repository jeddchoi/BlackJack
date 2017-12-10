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
	
	void setPlayer(Player who)
	{
		this->name = who.name;
		this->num = who.num;
		this->balance = who.balance;
		this->winingRate = who.winingRate;
	}
	void showPlayerInfo() // ??추가적인 코딩필요? 해당 내용의 목적이 궁금
	{
		cout<<"showPlayerInfo()"<<endl;
	}
};

bool cmpNum(const Player &a, const Player &b){
	return a.getNum() < b.getNum();
}

bool cmpBalance(const Player &a, const Player &b){
	return a.getBalance() > b.getBalance();
}

class GamePlayer : public Player
{
protected:
	vector<Card> * Hand;
	double Starting_balance;
	double Bet;
	double Sum;
	double insurance;
	
	double accMinus;
	double accPlus;
	
public:
	GamePlayer(int num, string name, double balance, double rate) : Player(num, name, balance, rate)
	{}
	GamePlayer() : Player()
	{}
	~GamePlayer()
	{}
	
	bool canBet(int money)
	{
		if(this->balance >= money){
			return true;
		}
		else{
			return false;
		}
	}

	double getBet()
	{
		return this->Bet;
	}

	double setInsurance(double insurance){
		this->insurance = insurance;
	}
	
	void plusBet(int money) 
	{
		//this->balance -= money;
		this->Bet += money;
	}
	void setCards() //노필요 인듯?
	{}
	void setStartingBalance()
	{
		this->Starting_balance = this->balance;
		this->balance -= this->Bet;
	}
	
	double getStartingBalance()
	{
		return this->Starting_balance;
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



class Dealer : public GamePlayer
{
public:
	
	
};
