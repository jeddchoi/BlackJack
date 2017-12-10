#pragma once
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;
class Game
{
protected:
	vector<Player> Players; // 등록된 플레이어들

public:
	Game()
	{
		loadPlayers();// 게임 시작 시 players.txt에서 플레이어 목록 로딩
	}
	
	~Game()
	{
		storePlayers();// 게임 종료 시 players.txt에 플레이어 목록 저장
	}
	
	// 완성
	void loadPlayers()
	{
		ifstream fin;
		fin.open("players.txt");
		
		int numofplayers;
		
		fin>>numofplayers;
		
		int num;
		string playerName;
		double balance;
		double winningRate;
		
		for(int i = 0; i < numofplayers; i++ )
		{
			fin>>num>>playerName>>balance>>winningRate;
			Players.push_back(Player(num, playerName, balance, winningRate));
		}
		fin.close();
	}
	
	// 완성
	void storePlayers()
	{
		ofstream fout;
		fout.open("players.txt");
		
		sort(Players.begin(), Players.end(), cmpNum);
		fout<<Players.size()<<endl;
		
		
		for(int i = 0; i < Players.size(); i++ )
		{
			fout<<Players[i].getNum()<<" "<<Players[i].getName()<<" "<<Players[i].getBalance()<<" "<<Players[i].getRate()<<endl;
		}
		fout.close();
	}
	
	// 완성)게임 첫 화면 출력
	void showIntro()
	{
	/*
	 먼저 loadPlayers() 통해서 players.txt로부터 Players 로딩
	 1. 새로운 플레이어 등록
	 2. 기존 플레이어로 게임 시작
	 3. 잔고 기준 플레이어 랭킹 출력
	 4. 기존 플레이어 게임머니 충전하기
	 5. 라이센스 출력 혹은 게임방법 출력
	 6. 게임 종료
	 */
		printLine();
		
		cout<<"1. Register new Player.(R or r)"<<endl;
		cout<<"2. Game start if you have registered.(G or g)"<<endl;
		cout<<"3. Show players status.(S or s)"<<endl;
		cout<<"4. Charge your money.(C or c)"<<endl;
		cout<<"5. Information : How to game and Who make this game.(I or i)"<<endl;
		cout<<"6. End game.(E or e)"<<endl;
		
		printLine();
		
		cout<<"Whick menu are you going to choose? : ";
	}
	
	// 플레이어의 인덱스를 반환하고 없으면 -1반환
	int getRegisteredPlayerIdx(string playerName)
	{
		int idx = 0;
		int result = -1;
		while(idx < Players.size())
		{
			if(Players[idx].getName() == playerName)
			{
				result = idx;
				break;
			}
			idx++;
		}
		
		return result;
	}
	
	
	
	// 완성)#1. 새로운 플레이어 등록
	void addNewPlayer()
	{
	/*
	 1. 이름 입력
	 2. ->입력한 이름이 이미 있는 이름이면 메뉴 첫화면으로 return
	 3. ->입력한 이름이 없으면 이름 입력 받고 그 이름으로 fillUp() 호출해 게임머니 충전하고 메뉴 첫화면으로 return
	 */
		string playerName;
		
		cout<<"Enter your name. : ";
		cin>>playerName;
		if( getRegisteredPlayerIdx(playerName) != -1 )
		{
			cout<<endl<<"You already have registered you name."<<endl;
			return;
		}
		else
		{
			Player newPlayer((unsigned int)Players.size(), playerName, 0, 0);
			Players.push_back(newPlayer);
			fillUp(playerName);
		}
	}
	
	
	// #2. 기존 플레이어로 게임 시작
	virtual void startGame()
	{
	/*
	 이 부분은 BlackJack 클래스의 멤버함수로 함
	 */
	}
	// 완성)#3. 잔고 기준 플레이어 랭킹 출력
	void showPlayers()
	{
	/*
	 벡터로 선언된 Players의 랭킹 출력
	 1. 순번 2. 이름 3. 잔고 4. 승률
	 */
		sort(Players.begin(), Players.end(), cmpBalance);
		
		cout.setf(ios::left, ios::adjustfield);
		
		printLine();
		cout<<setw(4)<<"Num"<<setw(20)<<"Player's name"<<setw(10)<<"Balance"<<setw(10)<<"Wining Rate"<<endl;
		printLine();
		for(int i = 0; i < Players.size(); i++ )
		{
			cout<<setw(4)<<Players[i].getNum()<<setw(20)<<Players[i].getName();
			cout<<setw(10)<<Players[i].getBalance()<<setw(10)<<Players[i].getRate()<<endl;
		}
		printLine();
		
		sort(Players.begin(), Players.end(), cmpNum);
	}
	
	// 완성)#4. 기존 플레이어 게임머니 충전하기
	void fillUp(string playerName = "")
	{
	/*
	 1. 메뉴 첫 화면에서 들어온 경우 : ->playerName == "" 이다.
		 이름을 입력 받아서 Players에서 검색후 이름이 있으면 충전할 금액 입력받아서 업데이트 하기
									   이름이 없으면 오류 문구 출력하고 메뉴 첫화면으로 return
	 2. 새로운 플레이어 등록, 혹은 게임 중에서 들어온 경우 : playerName != "" 이다.
	     충전할 금액 입력 받아서 Players의 end()의 잔고를 업데이트 한 후 메뉴 첫화면으로 return
	 */
		
		if(playerName == "")
		{
			cout<<"Enter your name. : ";
			cin>>playerName;
		}
		
		int idx = getRegisteredPlayerIdx(playerName);
		if( idx == -1 )
		{
			cout<<endl<<"Your Name ["<<playerName<<"] does not exist. "<<endl;
			return;
		}
		
		double money;
		cout<<"Enter the amount as you want to charge. : ";
		cin>>money;
		
		Players[idx].setBalance(money);
		Players[idx].showPlayerInfo(); // 업데이트 된 정보 출력
	}
	
	// 완성)#5. 라이센스 출력
	void showLicence()
	{
	/*
	 2. 라이센스 출력
	 */
		cout<<"-----------------------------------------------------------------"<<endl;
		cout<<"|           - =-=-=- Who made this Game -=-=-=-                 |"<<endl;
		cout<<"|                                                               |"<<endl;
		cout<<"|            1. Taekyoung Oh                                    |"<<endl;
		cout<<"|            2. Seoyeon Choi                                    |"<<endl;
		cout<<"|            3. Gwangyoung Choi                                 |"<<endl;
		cout<<"|                                                               |"<<endl;
		cout<<"|                                                               |"<<endl;
		cout<<"|                                                               |"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;
	}
	
	// 완성)#6. 게임 종료
	void exit()
	{
	/*
	 1. storePlayers() 통해서 Players를 players.txt 파일에 다시 저장하고
	 2. "Thank you for playing" 출력후
	 3. return
	 */
		storePlayers();
		cout<<"Thank you for playing."<<endl;
	}
	
	void printLine()
	{
		cout<<"-----------------------------------------------------------------"<<endl;
	}
};

class BlackJack : public Game
{
protected:
	GamePlayer currentPlayer; // 현재 게임하는 사람
	Dealer Computer; // 딜러
	Deck deck; // 총 52장의 카드
	int player_draw; // 플레이어가 몇 번 카드를 드로우 했는지.

public:
	BlackJack() : Game()
	{
		player_draw = 0;
	}
	~BlackJack()
	{}
	
	// 테스트)현재 게임하는 사람 로딩 : 성공하면 true, 실패하면 false 반환
	bool loadPlayer()
	{
		string playerName;
		cout<<"Enter your name. : ";
		cin>>playerName;
		
		int idx = getRegisteredPlayerIdx(playerName);
		
		if( idx == -1 )
		{
			cout<<endl<<"Your Name ["<<playerName<<"] does not exist. "<<endl;
			return false;
		}
		currentPlayer.setPlayer(Players[idx]);
		return true;
	}

	// 테스트)플레이어가 베팅하기 : 정상적으로 베팅되었으면 true 반환, 아니면 false 반환
	bool doBetting()
	{
		double money;
		//-> Starting_Balance에 Balance를 백업하고 Balance에서 베팅금액을 뺀다.
		currentPlayer.setStartingBalance();
		
		while(true)
		{
			try{
				cout<<"How much do you want to bet? :";
				cin>>money;
				cin.ignore();
				
				if(!isdigit(money))
					throw money;
				
				if(currentPlayer.canBet(money))
				{
					currentPlayer.plusBet(money); // 베팅금액을 덮어씌우는게 아니라 더해야 함.
					currentPlayer.showPlayerInfo();
					return true;
				}
				else
				{
					cout<<"You don't have enough money."<<endl;
					cout<<"You go to main menu."<<endl;
					return false;
				}
			}
			catch(char exception)
			{
				cout<<"Please Try Again."<<endl;
				cin.clear();
			}
		}
	}
	
	void showFirstCards() // 딜러는 오픈카드만, 플레이어는 두 장의 첫 카드를 보여준다.
	{
		Computer.showOpenCard();
		currentPlayer.showFirstTwoCards();
	}
	
	void showHand(GamePlayer p) // 딜러인지 플레이어 인지 인수로 받아서 핸드에 가지고 있는 모든 카드를 보여준다.
	{
		p.showHand();
	}
	
	// 게임 시작시 두 장의 카드 받기
	int getTwoCards()
	{
		currentPlayer.drawCards(deck);
		Computer.drawCards(deck);
		player_draw++;
		
		if(Computer.isOpenCardAce())
		{
			if(currentPlayer.isFirstCardsBJ())
				return 1; // 딜러의 오픈카드가 에이스이고, 플레이어가 블랙잭인 경우
			else
				return 2; // 딜러의 오픈카드가 에이스이고, 플레이어가 블랙잭이 아닌 경우
		}
		else
		{
			if(currentPlayer.isFirstCardsBJ())
			{
				if(Computer.isFirstCardsBJ())
					return 3; // 딜러의 오픈카드가 에이스가 아니고, 플레이어와 딜러 둘다 블랙잭인 경우
				else
					return 4; // 딜러의 오픈카드가 에이스 아니고, 플레이어는 블랙잭인데 딜러는 블랙잭이 아닌 경우
			}
			else
			{
				if(Computer.isFirstCardsBJ())
					return 5; // 딜러의 오픈 카드가 에이스가 아니고, 플레이어는 블랙잭이 아닌데 딜러가 블랙잭인 경우
				else
					return 6; // 딜러의 오픈 카드가 에이스가 아니고, 플레이어와 딜러 둘다 블랙잭이 아닌 경우
				
			}
		}
	}
	
	// 플레이어가 어떤 일할지 메뉴 출력하기
	void showPlayerWhatToDo()
	{
		/*
	  1. STAY 2. HIT 3. DOUBLEDOWN 4. SURRENDER(2번째부터는 비활성화)
	  */
		cout<<"What do you want to do?"<<endl;
		printLine();
		
		cout<<"1. Stay.(S or s)"<<endl;
		cout<<"2. Hit.(H or h)"<<endl;
		cout<<"3. Double down.(D or d)"<<endl;
		if(player_draw == 1)
			cout<<"4. Surrender. (G or g)"<<endl;
		printLine();
	}
	
	// 플레이어 턴에 할일 : 블랙잭이나 버스트가 아닐 경우
	int doPlayerTurn()
	{/*
		* 플레이어 할일 :(플레이어가 블랙잭인 경우는 이미 다뤄졌음)
		** 메뉴를 출력한다. -> 메뉴를 선택한다.
		(1) STAY -> turn을 딜러로 넘긴다.
		(2) HIT -> 추가 카드를 받는다. -> 추가 카드를 출력한다.
	  		(a) 합이 22 이상이다 -> 베팅금액 잃고 게임 끝(5)
	  		(b) 합이 21 이하이다 -> 1)로 간다. ->SURRENDER 비활성화
		(3) DOUBLEDOWN -> 추가 카드를 받고 베팅금액이 2배가 된다.(Balance에서 베팅금액 한 번 더 빠짐) -> 추가 카드를 출력한다.
	  		(a) 합이 22 이상이다 -> 모든 베팅금액 잃고 게임 끝(5)
	  		(b) 합이 21 이하이다 -> turn을 딜러로 넘긴다.
		(4) SURRENDER -> 베팅금액의 1/2만 다시 Balance에 충전되고 게임 끝(6)
		*/
		
		char response;
		int result = -1;
		while(true)
		{
			try{
				showPlayerWhatToDo();
				// 메뉴 선택
				cin>>response;
				cin.ignore();
				
				if(!isalpha(response))
					throw response;
				
				switch (response) {
					// STAY
					case 'S':
					case 's':
						result = 1; // STAY
						break;
					// HIT
					case 'H':
					case 'h':
						currentPlayer.drawCard(deck);
						player_draw++;
						showHand(currentPlayer);
						if(currentPlayer.getCardSum() > 21)
						{
							result = 5; // BURST
							break;
						}
						else
						{
							continue;
						}
						
					// DOUBLE DOWN
					case 'D':
					case 'd':
						if(currentPlayer.canBet(currentPlayer.getBet() *2))
							currentPlayer.plusBet(currentPlayer.getBet());
						else
						{
							cout<<"You don't have enough money."<<endl;
							continue;
						}
						currentPlayer.drawCard(deck);
						player_draw++;
						showHand(currentPlayer);
						if(currentPlayer.getCardSum() > 21)
						{
							result = 5; //BURST
							break;
						}
						else
						{
							continue;
						}
					
					// SURRENDER if
					if(player_draw == 1)
					{
						case 'G':
						case 'g':
							result = 6; // SURRENDER
							break;
					}
					default:
						continue;
				}
				break;
			}
			catch(char exception)
			{
				cout<<"Please Try Again."<<endl;
				cin.clear();
			}
		}
		return result;
	}
	
	// 딜러 턴에 할 일 : 플레이어가 할일 다 한 경우
	int doDealerTurn()
	{
		/*
		* 딜러가 할일 :(딜러의 오픈카드가 에이스인 경우, 딜러가 블랙잭인 경우는 이미 다뤄졌음)
		** 히든카드를 출력한다.
		(1) 합이 16 이하다. -> 추가 카드를 획득한다. -> 추가 카드를 출력한다. -> 다시 분기로 이동
		(2) 합이 22 이상이다. -> 딜러가 버스트했으므로 플레이어는 베팅금액 + 베팅금액을 받는다. -> 게임 끝(2)
		(3) 합이 21 이하이다. -> 플레이어의 카드 합과 비교한다.
		 	(a) 플레이어가 합이 더 크다. -> 플레이어가 이겼으므로 베팅금액 + 베팅금액을 받는다. -> 게임 끝(2)
		 	(b) 딜러가 합이 더 크다. -> 플레이어는 베팅금액을 잃는다. -> 게임 끝(5)
		 	(c) 합이 같다. -> push이므로 베팅금액만 그대로 돌려받는다. -> 게임 끝(3)
		 */
		int result = -1;
		bool cont = true;
		while(cont)
		{
			showHand(Computer);
			int sum = Computer.getCardSum();
			if(sum <= 16)
			{
				Computer.drawCard(deck);
				cont = true;
			}
			else if(sum >= 22)
			{
				cont = false;
				cout<"Dealer burst!"<<endl;
				result = 2; // 딜러가 졌음
			}
			else
			{
				cont = false;
				int tmp = compareSum(currentPlayer, Computer);
				if(tmp == 1) // 카드합 : 플레이어 > 딜러
					result = 2; // 딜러가 졌음
				else if(tmp == -1) // 카드합 : 플레이어 < 딜러
					result = 5; // 플레이어가 졌음
				else // 카드합 : 플레이어 == 딜러
					result = 3; // 플레이어와 딜러 비김
			}
		}
		return result;
	}
	// 딜러 카드의 합과 플레이어 카드의 합 비교
	int compareSum(GamePlayer& p1, GamePlayer& p2)
	{
		int sum1 = p1.getCardSum();
		int sum2 = p2.getCardSum();
		
		if(sum1 < sum2)
			return -1;
		else if(sum1 > sum2)
			return 1;
		else
			return 0;
	}
	
	// 어떤 케이스냐에 따라 처리하는 결과가 달라짐
	void getResult(int result)
	{
		/*
		 1 -> 플레이어가 BLACKJACK인 경우 : 베팅금액 + 베팅금액 * 1.5를 돌려받기
		 2 -> 플레이어가 win한 경우 : 베팅금액 + 베팅금액을 돌려받기
		 3 -> push 인 경우 : 베팅금액을 돌려받기
		 4 -> 인슈런스 성공인 경우 : 인슈런스 금액 + 인슈런스 금액 * 2를 돌려받기
		 5 -> 모든 실패의 경우 : 그냥 끝
		 6 -> 플레이어가 SURREND한 경우 : 베팅금액의 1/2를 돌려받기
		 
		 */
		int bet = currentPlayer.getBet();
		int insurance = currentPlayer.getInsurance();
		switch (result) {
			case 1:
				cout<<"BLACK JACK!"<<endl;
				currentPlayer.setBalance(bet + bet * 1.5);
				break;
			
			case 2:
				cout<<"You Win!"<<endl;
				currentPlayer.setBalance(bet + bet);
				break;
				
			case 3:
				cout<<"Push!"<<endl;
				currentPlayer.setBalance(bet);
				break;
				
			case 4:
				cout<<"Insuranse hit!"<<endl;
				currentPlayer.setBalance(insurance + insurance * 2);
				break;
				
			case 5:
				cout<<"You Fail!"<<endl;
				break;
				
			case 6:
				cout<<"You Surrender!"<<endl;
				currentPlayer.setBalance(bet * 0.5);
				break;
				
			
			default:
				break;
		}
	}
	
	
	
	bool wannaEvenMoney()
	{
		cout<<"Do you want to Even money?(Y/N) :";
		char response;
		while(true)
		{
			try{
				// 메뉴 선택
				cin>>response;
				cin.ignore();
				
				if(!isalpha(response))
					throw response;
				
				switch (response) {
					case 'Y':
					case 'y':
						return true;
					case 'N':
					case 'n':
						return false;
					default:
						continue;
				}
				break;
			}
			catch(char exception)
			{
				cout<<"Please Try Again."<<endl;
				cin.clear();
			}
		}
	}
	
	bool wannaInsurance()
	{
		cout<<"Do you want to Insurance?(Y/N) :";
		char response;
		while(true)
		{
			try{
				// 메뉴 선택
				cin>>response;
				cin.ignore();
				
				if(!isalpha(response))
					throw response;
				
				switch (response) {
					case 'Y':
					case 'y':
						if(currentPlayer.canBet(currentPlayer.getBet() / 2)) // 추가적으로 베팅금의 반만큼 베팅 할 수 있나?
						{
							currentPlayer.setInsurance(currentPlayer.getBet() / 2);
							return true;
						}
						else
						{
							cout<<"You don't have enough money.";
							return false;
						}
					case 'N':
					case 'n':
						return false;
					default:
						continue;
				}
				break;
			}
			catch(char exception)
			{
				cout<<"Please Try Again."<<endl;
				cin.clear();
			}
		}
	}
	
	bool wannaRestart()
	{
		cout<<"Do you want to restart the Game?(Y/N) :";
		char response;
		while(true)
		{
			try{
				// 메뉴 선택
				cin>>response;
				cin.ignore();
				
				if(!isalpha(response))
					throw response;
				
				switch (response) {
					case 'Y':
					case 'y':
						return true;
					case 'N':
					case 'n':
						return false;
					default:
						continue;
				}
				break;
			}
			catch(char exception)
			{
				cout<<"Please Try Again."<<endl;
				cin.clear();
			}
		}
	}
	virtual void startGame()
	{
		/*
		 1. 카드를 섞는다.
		 2. 플레이어가 베팅을 한다. -> Starting_Balance에 Balance를 백업하고 Balance에서 베팅금액을 뺀다.
		 3. 플레이어가 카드 1장 받고 딜러가 히든카드 1장 받는다. 그리고 다시 플레이어, 딜러 각각 1장씩 받는다.
		 4. 각 패를 보여준다.
		 5. 만약, 딜러의 오픈 카드가 에이스다. :
		 1) 플레이어는 블랙잭이다. -> 이븐머니 여부를 묻는다.
		 (1) 이븐머니 한다 -> 딜러의 히든카드를 보여준다.
		 (a) 딜러가 블랙잭 여부 상관없이 -> 베팅금액 + 베팅금액(승리수당)을 받는다. -> 게임 끝(2)
		 (2) 이븐머니 하지 않는다. -> 딜러의 히든카드를 보여준다.
		 (a) 딜러가 블랙잭이다. -> push이므로(비겼으므로) 베팅금액만을 그대로 다시 돌려 받는다. -> 게임 끝(3)
		 (b) 딜러가 블랙잭이 아니다. -> 베팅금액 + 베팅금액*1.5를 받는다. -> 게임 끝(1)
		 2) 플레이어가 블랙잭이 아니다. ->인슈런스 여부를 묻는다.
		 (1) 인슈런스를 한다 -> (베팅액의 절반을 Balance에서 뺀다.) -> 플레이어 할일 한다. -> 딜러의 히든카드를 보여준다.
		 (a) 딜러가 블랙잭이다. -> 보험금 + 보험금*2 를 받는다. -> 게임 끝(4)
		 (b) 딜러가 블랙잭이 아니다. -> 보험금은 잃고 딜러가 할일 한다.-> 결과에 따라 계산한다. -> 게임 끝
		 (2) 인슈런스를 하지않는다. -> 플레이어 할일 한다. -> 딜러의 히든카드를 보여준다.
		 (a) 딜러가 블랙잭이다. -> 베팅금액을 잃는다. -> 게임 끝(5)
		 (b) 딜러가 블랙잭이 아니다. -> 딜러가 할일 한다. -> 결과에 따라 계산한다. -> 게임 끝
		 - 딜러의 오픈카드가 에이스가 아니다. :
		 1) 플레이어는 블랙잭이다.
		 (1) 딜러도 블랙잭이다.(21) -> push이므로(비겼으므로) 베팅금액만을 그대로 다시 돌려 받는다. -> 게임 끝(3)
		 (2) 딜러가 할일한다. -> 결과에 따라 계산한다. -> 게임 끝
		 2) 플레이어가 블랙잭이 아니다.
		 (1) 딜러는 블랙잭이다.(21) -> 딜러가 이겼다. -> 게임 끝
		 
		 (2) 딜러가 할일 한다. -> 결과에 따라 계산한다. -> 게임 끝
		 
		 6. 게임끝이면 다시 게임할건지 묻는다.
		 1) 다시 할거다. -> 1.로 간다.
		 2) 끝낸다. -> 지금까지의 게임 결과 출력하고 updatePlayer()로 currentPlayer를 Players에 업데이트한 후 return
		 
		 * 플레이어 할일 :(플레이어가 블랙잭인 경우는 이미 다뤄졌음)
		 ** 메뉴를 출력한다. -> 메뉴를 선택한다.
		 (1) STAY -> turn을 딜러로 넘긴다.
		 (2) HIT -> 추가 카드를 받는다. -> 추가 카드를 출력한다.
		 (a) 합이 22 이상이다 -> 베팅금액 잃고 게임 끝(5)
		 (b) 합이 21 이하이다 -> 1)로 간다. ->SURRENDER 비활성화
		 (3) DOUBLEDOWN -> 추가 카드를 받고 베팅금액이 2배가 된다.(Balance에서 베팅금액 한 번 더 빠짐) -> 추가 카드를 출력한다.
		 (a) 합이 22 이상이다 -> 모든 베팅금액 잃고 게임 끝(5)
		 (b) 합이 21 이하이다 -> turn을 딜러로 넘긴다.
		 (4) SURRENDER -> 베팅금액의 1/2만 다시 Balance에 충전되고 게임 끝(6)
		 
		 * 딜러가 할일 :(딜러의 오픈카드가 에이스인 경우, 딜러가 블랙잭인 경우는 이미 다뤄졌음)
		 ** 히든카드를 출력한다.
		 (1) 합이 16 이하다. -> 추가 카드를 획득한다. -> 추가 카드를 출력한다. -> 다시 분기로 이동
		 (2) 합이 22 이상이다. -> 딜러가 버스트했으므로 플레이어는 베팅금액 + 베팅금액을 받는다. -> 게임 끝(2)
		 (3) 합이 21 이하이다. -> 플레이어의 카드 합과 비교한다.
		 (a) 플레이어가 합이 더 크다. -> 플레이어가 이겼으므로 베팅금액 + 베팅금액을 받는다. -> 게임 끝(2)
		 (b) 딜러가 합이 더 크다. -> 플레이어는 베팅금액을 잃는다. -> 게임 끝(5)
		 (c) 합이 같다. -> push이므로 베팅금액만 그대로 돌려받는다. -> 게임 끝(3)
		 */
		
		bool cont;
		if(loadPlayer()) // 이름 입력 받아서 플레이어 정보를 로딩한다.
			cont = true;
		else
			return;
		
		while(cont)
		{
			Computer.initHand(); // 딜러 핸드 초기화
			deck.init(); // 52장 카드로 초기화한다.
			deck.shuffleDeck(); // 덱의 카드들을 섞는다.
			currentPlayer.initGame(); // 카드와 베팅금액을 비운다.
			Computer.initGame(); // 카드를 비운다.
			doBetting(); // player는 베팅을 한다.
			int first_result = getTwoCards();
			
			showFirstCards();
			switch (first_result)
			{
				case 1: // 딜러의 오픈카드가 에이스이고, 플레이어가 블랙잭인 경우
					if(wannaEvenMoney()) // 이븐 머니 한다면
					{
						Computer.revealRestCard(); // 딜러의 히든 카드를 보여줌
						getResult(2); // 2번 결과로 처리
						continue; // 게임 종료
					}
					else
					{
						Computer.revealRestCard(); // 딜러의 히든 카드를 보여줌
						if(Computer.isFirstCardsBJ()) // 딜러가 블랙잭이면
							getResult(3); // 3번 결과로 처리
						else // 딜러가 블랙잭이 아니면
							getResult(1); // 1번 결과로 처리
						continue;
					}
				case 2: // 딜러의 오픈카드가 에이스이고, 플레이어가 블랙잭이 아닌 경우
					if(wannaInsurance())
					{
						Computer.revealRestCard(); // 딜러의 히든 카드를 보여줌
						if(Computer.isFirstCardsBJ()) // 딜러가 블랙잭이면
							getResult(4); // 3번 결과로 처리
						else // 딜러가 블랙잭이 아니면
						{
							int tmp = doDealerTurn();
							getResult(tmp);
						}
					}
					else
					{
						int tmp = doPlayerTurn();
						if(tmp == 1) // 플레이어가 stay해서 비교해야함
						{
							int tmp2 = compareSum(currentPlayer, Computer);
							if(tmp2 == 1) // 카드합 : 플레이어 > 딜러
								result = 2; // 딜러가 졌음
							else if(tmp2 == -1) // 카드합 : 플레이어 < 딜러
								result = 5; // 플레이어가 졌음
							else // 카드합 : 플레이어 == 딜러
								result = 3; // 플레이어와 딜러 비김
							getResult(tmp2);
						}
						else // 플레이어가 버스트 혹은 서렌더한 경우
							getResult(tmp);
					}
					continue; // 게임 종료
				case 3: // 딜러의 오픈카드가 에이스가 아니고, 플레이어와 딜러 둘다 블랙잭인 경우
					getResult(3);
					continue; // 게임 종료
				case 4: // 딜러의 오픈카드가 에이스 아니고, 플레이어는 블랙잭인데 딜러는 블랙잭이 아닌 경우
					int tmp = doDealerTurn();
					getResult(tmp);
					continue; // 게임 종료
				case 5: // 딜러의 오픈 카드가 에이스가 아니고, 플레이어는 블랙잭이 아닌데 딜러가 블랙잭인 경우
					getResult(5);
					continue; // 게임 종료
				case 6: // 딜러의 오픈 카드가 에이스가 아니고, 플레이어와 딜러 둘다 블랙잭이 아닌 경우
					int tmp = doDealerTurn();
					getResult(tmp);
					continue; // 게임 종료
				
				default:
					break;
			}
			
			if(wannaRestart())
			{
				cont = true;
				
			}
			else
				cont = false;
		}
		updatePlayer();
		showGameResult();
	}
	
	// Players에 이번 플레이어의 정보 업데이트
	void updatePlayer()
	{
		int idx = getRegisteredPlayerIdx(currentPlayer.getName());
		Players[idx].setPlayer(currentPlayer);
	}
	
	// 이번 게임 종료시 결과 출력
	void showGameResult()
	{
	/*
	 1. 이름
	 2. 잔고
	 3. 누적 획득 금액 (최종으로 잃었을 경우 -로 표시)
	 5. 랭킹
	 */
	}
};
