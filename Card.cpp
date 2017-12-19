#include "Card.h"

using namespace std;


Card::Card() { cards = 52; }
Card::~Card() {};
Card::Card(const Card & ca)
{
	value = ca.value;
	cards = ca.cards;
	shp = ca.shp;
	number = ca.number;
	cardName = ca.cardName;
}
void Card::setCard(int cardName) {
	setShape(cardName);
	setValue(cardName);
	setNumber(cardName);
}

void Card::setShape(int cardName) {
	if (cardName < 10)
		shp = cardName;
	else if (10 < cardName && cardName < 50)
		shp = cardName / 10;
	else if (50 < cardName) {
		shp = cardName / 100;
	}
}

void Card::setValue(int cardName) {
	if (cardName < 10)
		value = 11;                     // A를 무조건 11로 처리
	else if (10 < cardName && cardName < 50)
		value = cardName % 10;
	else if (50 < cardName)
		value = 10;
}

void Card::setNumber(int cardName) {
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

char Card::getShape() {
	char shape;
	if(number > 10){
		if (shp == 1){
			shape = 'D';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ◆        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<(char)number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ◇ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
		else if (shp == 2){
			shape = 'S';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ♠        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<(char)number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ♤ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
		else if (shp == 3){
			shape = 'H';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ♥        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<(char)number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ♡ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
		else if (shp == 4){
			shape = 'C';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ♣        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<(char)number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ♧ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
	} else {
		if (shp == 1){
			shape = 'D';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ◆        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ◇ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
		else if (shp == 2){
			shape = 'S';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ♠        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ♤ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
		else if (shp == 3){
			shape = 'H';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ♥        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ♡ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
		else if (shp == 4){
			shape = 'C';
			cout<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
			cout<<"| ♣        |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|    "<<number<<"     |"<<endl;
			cout<<"|          |"<<endl;
			cout<<"|       ♧ |"<<endl;
			cout<<" ㅡㅡㅡㅡㅡ"<<endl;
		}
	}
	return shape;
}

int Card::getNumber() {
	return number;
}

int Card::getValue() {
	return value;
}


Deck::Deck() {
	cards.reserve(52);
	init();
}
Deck::~Deck() {};

void Deck::shuffleDeck()
{
//	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
//	random_shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	std::random_device rd;
	std::mt19937 g(rd());
	
	std::shuffle(cards.begin(), cards.end(), g);
}

int Deck::getRemainCardsNum() {
	return (int)cards.size();
}


Card Deck::getACard() {
	Card card;
	if (cards.size() >= 1) {
		card = cards[cards.size() - 1];
		cards.pop_back();
		card.Card::setCard(card.cardName);
	}
	else {
		cout << "There are no cards." << endl;
		exit(-1);
	}
	return card;
}

void Deck::init() {
	Card new_card;
	int arr[52] = { 1, 2, 3, 4, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45, 46, 47, 48, 49, 100, 110, 120, 130, 200, 210, 220, 230, 300, 310, 320, 330, 400, 410, 420, 430 };
	cards.clear();
	for (int i = 0; i < 52; i++) {
		new_card.cardName = arr[i];
		cards.push_back(new_card);
	}
}



