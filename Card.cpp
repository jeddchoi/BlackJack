#include "Card.h"

Card::Card(int number){
	this->number = number;
}


void Card::setCard(char shape, int number){
	Card::setShape(shape);
	Card::setValue(number);
}


void Card::setShape(char shape){
	if(shape == 'D')
		shp = 1;
	else if(shape == 'S')
		shp = 2;
	else if(shape == 'H')
		shp = 3;
	else if(shape == 'C')
		shp = 4;
}


void Card::setValue(int number){
	int sum = GamePlayer::sum ;

	if(2 <= number && number <=9){
		value = number;
		Card::cardName = shp * 10 + value;
	}
	else if(number == 10 || number == 'K' || number == 'J' || number == 'Q'){
		value = 10;
		shp *= 100;
		if(number == 10)
			cardName = shp;
		else if(number == 'K')
			cardName = shp + 10;
		else if(number == 'J')
			cardName = shp + 20;
		else if(number == 'Q')
			cardName = shp + 30;
	}
	else if(number == 1){
		cardName = shp;
		if(sum <= 10)
			value = 11;
		else 
			value = 1;
	}
}


char Card::getShape(int shp)
{
	char shape;

	if(shp == 1)
		shape = 'D';
	else if (shp == 2)
		shape = 'S';
	else if(shp == 3)
		shape = 'H';
	else if(shp == 4)
		shape = 'C';

	return shape;
}


int Card::getNumber()
{
	int number;

	if(cardName < 10)
		number = 'A'; //65
	else if(10 < cardName && cardName < 50)
		number = cardName%10;
	else if(50 < cardName){
		if(cardName%100 == 0)
			number = 10;
		else if(cardName%100 == 10)
			number = 'K'; //75
		else if(cardName%100 == 20)
			number = 'J'; //74
		else if(cardName%100 == 30)
			number = 'Q'; //81
	}

	return number;
}


int Card::getValue()
{
	return value;
}



// 52장으로 이루어져 있는 카드 생성하기
Deck::Deck(){
	cards.reserve(52);
	init();
}


// 덱 카드 순서 섞기
void Deck::shuffleDeck(){
	for(int i = 0; i < 100; i++){
		Card temp;
		int left;
		int right;

		left = rand()%CARD::CARDNUMBER;
		right = rand()%CARD::CARDNUMBER;
		temp = cards[left];
		cards[left] = cards[right];
		cards[right] = temp;
	}
}


// 덱에 남아있는 카드 갯수 반환하기
int Deck::getRemainCardsNum(){
	return cards.size();
}


// 덱에서 맨 위에(뒤에) 있는 카드 뽑기
Card Deck::getACard(){
	Card card;
	char shape;
	if(cards.size >=1){
		card = cards[cards.size()-1];
		cards.pop_back();

		/*********************************
		이부분은 안넣어도 되는걸까?
		
		if(card < 10){
			shape = Card::getShape(card);
			Card::setCard(shape, card);
		} 
		else if(10<card && card<50){
			shape = Card::getShape(card/10);
			Card::setCard(shape, card);
		}
		else if(100<card){
			shape = Card::getShape(card/100);
			Card::setCard(shape, card);
		}
		
		************************************/

	} else{
		cout << "There is no cards."<<endl;
		return 0;
	}
	return card;
}


void Deck:: init() {
	int arr[52] = { 1, 2, 3, 4, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45, 46, 47, 48, 49, 100, 110, 120, 130, 200, 210, 220, 230, 300, 310, 320, 330, 400, 410, 420, 430 };
	cards.clear();
	for(int i = 0; i < 52; i++){
		cards.push_back(arr[i]);
	}
}
