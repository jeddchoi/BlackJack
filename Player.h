#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Player
{
protected:
    string Name;
    int Balance;

public:
	Player();
	~Player();
	string getName();
	int getBalance();
	
	
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

class Dealer : public GamePlayer
{
public:
	
	
};
