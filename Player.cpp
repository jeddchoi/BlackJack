
#include "Player.h"
using namespace std;


Player::Player(int num, string name, double balance) : num(num), name(name), balance(balance)
{}

Player::Player()
{}
Player::~Player()
{}

int Player::getNum() const
{
	return num;
}
string Player::getName() const
{
	return name;
}
double Player::getBalance() const
{
	return balance;
}

void Player::setBalance(double money)
{
	balance += money;
}

void Player::setPlayer(Player who)
{
	this->name = who.name;
	this->num = who.num;
	this->balance = who.balance;
}
void Player::showPlayerInfo()
{
	cout<<"플레이어 이름 : "<<this->name<<" 잔고 : "<< this->balance<<endl;
}


bool cmpNum(const Player &a, const Player &b){
	return a.getNum() < b.getNum();
}

bool cmpBalance(const Player &a, const Player &b){
	return a.getBalance() > b.getBalance();
}

GamePlayer::GamePlayer(int num, string name, double balance) : Player(num, name, balance)
{}
GamePlayer::GamePlayer() : Player()
{}
GamePlayer::~GamePlayer()
{}

bool GamePlayer::canBet(int money)
{
	if(this->balance >= money){
		return true;
	}
	else{
		return false;
	}
}


double GamePlayer::getBet()
{
	return this->Bet;
}

void GamePlayer::setInsurance(double insurance){
	this->insurance = insurance;
}

double GamePlayer::getInsurance(){
	return this->insurance;
}

void GamePlayer::plusBet(int money)
{
	this->balance -= money;
	this->Bet += money;
}

void GamePlayer::setStartingBalance()
{
	this->Starting_balance = this->balance;
	this->balance -= this->Bet;
}

double GamePlayer::getStartingBalance()
{
	return this->Starting_balance;
}

void GamePlayer::drawTwoCards(Deck &deck)
{
	(this->Hand).push_back(deck.getACard());
	(this->Hand).push_back(deck.getACard());
}

void GamePlayer::drawACard(Deck &deck)
{
	(this->Hand).push_back(deck.getACard());
}

void GamePlayer::showFirstTwoCards()
{
	cout<<"[ Player ]"<<endl;
	Hand[0].getShape();
	Hand[1].getShape();
	cout<<"[ "<<getSum<int>(Hand)<<" ]"<<endl;
	cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
}

double GamePlayer::getCardSum()
{
	this->Sum = getSum<int>(Hand);
	return this->Sum;
}

void GamePlayer::initGame(){
	this->Bet = 0;
	(this->Hand).clear();
}

bool GamePlayer::isFirstCardsBJ()
{
	this->Sum = getSum<int>(Hand);
	if(Sum == 21)
	{
		return true;
	}else
	{
		return false;
	}
}

void GamePlayer::showHand(){
	cout<<"[ Player ]"<<endl;
	vector<Card>::iterator i;
	for(i=Hand.begin(); i != Hand.end(); i++){
		(*i).getShape();
	}
	cout<<"[ "<<getSum<int>(Hand)<<" ]"<<endl;
	cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
}


// 딜러 카드의 합과 플레이어 카드의 합 비교
bool operator>(GamePlayer& p1, GamePlayer& p2)
{
	int sum1 = p1.getCardSum();
	int sum2 = p2.getCardSum();
	
	if(sum1 < sum2)
		return false;
	else if(sum1 > sum2)
		return true;
	else
		return false;
}

bool operator==(GamePlayer& p1, GamePlayer& p2)
{
	int sum1 = p1.getCardSum();
	int sum2 = p2.getCardSum();
	
	if(sum1 < sum2)
		return false;
	else if(sum1 > sum2)
		return false;
	else
		return true;
}
	
void Dealer::showOpenCard(){
	cout<<"[ Dealer ]"<<endl;
	Hand[1].getShape();
	cout<<"[ "<<Hand[1].getValue()<<" ]"<<endl;
	cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
}

bool Dealer::isOpenCardAce(){
	if(Hand[1].getNumber() == 'A')
		return true;
	else
		return false;
}

void Dealer::showHand(){
	cout<<"[ Dealer ]"<<endl;
	vector<Card>::iterator i;
	for(i=Hand.begin(); i != Hand.end(); i++){
		(*i).getShape();
	}
	cout<<"[ "<<getSum<int>(Hand)<<" ]"<<endl;
	cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
}
