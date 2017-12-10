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
	void showPlayerInfo()
	{
		cout<<"플레이어 이름 : "<<this->name<<" 잔고 : "<< this->balance <<" 승률 : "<< this->winingRate <<endl;
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
	vector<Card> Hand;
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
	
	void setInsurance(double insurance){
		this->insurance = insurance;
	}
	
	double getInsurance(){
		return this->insurance;
	}
	
	void plusBet(int money)
	{
		this->balance -= money;
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
	
	void drawTwoCards(Deck deck)
	{
		(this->Hand).push_back(deck.getACard());
		(this->Hand).push_back(deck.getACard());
	}
	
	void drawACard(Deck deck)
	{
		(this->Hand)->push_back(deck.getACard());
	}
	
	void showFirstTwoCards()
	{
		cout<<"shape : "<<Hand[0].getShape((Hand)[0].shp)<<" number : "<<Hand[0].getNumber()<<endl;
		cout<<"shape : "<<Hand[1].getShape((Hand)[1].shp)<<" number : "<<Hand[1].getNumber()<<endl;
	}
	
	double getCardSum()
	{
		this->Sum = getSum(Hand);
		return this->Sum;
	}
	
	void initGame(){
		this->Bet = 0;
		(this->Hand).clear();
	}
	
	bool isFirstCardsBJ()
	{
		this->Sum = getSum(Hand);
		if(Sum == 21)
		{
			return true;
		}else
		{
			return false;
		}
	}
	
	void showHand(){
		vector<Card>::iterator i;
		for(i=Hand.begin(); i != Hand.end(); i++){
			cout<<"shape : "<<(*i).getShape((*i).shp)<<" number : "<<(*i).getNumber()<<endl;
		}
	}
};



class Dealer : public GamePlayer
{
public:
	
	void showOpenCard(){
		cout<<"shape : "<<Hand[1].getShape(Hand[1].shp)<<" number : "<<Hand[1].getNumber()<<endl;
	}
	
	void revealRestCard()
	{
		cout<<"shape : "<<Hand[0].getShape(Hand[0].shp)<<" number : "<<Hand[0].getNumber()<<endl;
	}
	
	bool isOpenCardAce(){
		if(Hand[0].getNumber() == 'A')
			return true;
		else
			return false;
	}
	
};
