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
	Player(int num, string name, double balance) : num(num), name(name), balance(balance)
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
	
	void setBalance(double money)
	{
		balance += money;
	}
	
	void setPlayer(Player who)
	{
		this->name = who.name;
		this->num = who.num;
		this->balance = who.balance;
	}
	void showPlayerInfo()
	{
		cout<<"플레이어 이름 : "<<this->name<<" 잔고 : "<< this->balance<<endl;
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
	
	
public:
	GamePlayer(int num, string name, double balance) : Player(num, name, balance)
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
	
	void setStartingBalance()
	{
		this->Starting_balance = this->balance;
		this->balance -= this->Bet;
	}
	
	double getStartingBalance()
	{
		return this->Starting_balance;
	}
	
	void drawTwoCards(Deck &deck)
	{
		(this->Hand).push_back(deck.getACard());
		(this->Hand).push_back(deck.getACard());
	}
	
	void drawACard(Deck &deck)
	{
		(this->Hand).push_back(deck.getACard());
	}
	
	void showFirstTwoCards()
	{
		cout<<"[ Player ]"<<endl;
		Hand[0].getShape();
		Hand[1].getShape();
		cout<<"[ "<<getSum(Hand)<<" ]"<<endl;
		cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
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
		cout<<"[ Player ]"<<endl;
		vector<Card>::iterator i;
		for(i=Hand.begin(); i != Hand.end(); i++){
			(*i).getShape();
		}
		cout<<"[ "<<getSum(Hand)<<" ]"<<endl;
		cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
	}
};



class Dealer : public GamePlayer
{
public:
	
	void showOpenCard(){
		cout<<"[ Dealer ]"<<endl;
		Hand[1].getShape();
		cout<<"[ "<<Hand[1].getValue()<<" ]"<<endl;
		cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
	}
	
	bool isOpenCardAce(){
		if(Hand[1].getNumber() == 'A')
			return true;
		else
			return false;
	}
	
	void showHand(){
		cout<<"[ Dealer ]"<<endl;
		vector<Card>::iterator i;
		for(i=Hand.begin(); i != Hand.end(); i++){
			(*i).getShape();
		}
		cout<<"[ "<<getSum(Hand)<<" ]"<<endl;
		cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
	}
};
