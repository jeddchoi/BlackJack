#pragma once
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/*
 여유 있으면 split도 구현
 승률도 표시하기 
 덱 수를 여러개 랜덤으로 결정
 최광영 
 */

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
	
	void loadPlayers()
	{
		ifstream fin;
		fin.open("players.txt");
		
		int numofplayers;
		
		fin>>numofplayers;
		
		int num;
		string playerName;
		int balance;
		double winningRate;
		
		for(int i = 0; i < numofplayers; i++ )
		{
			fin>>num>>playerName>>balance>>winningRate;
			Players.push_back(Player(num, playerName, balance, winningRate));
		}
		fin.close();
	}
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
	
	void showIntro(); // 게임 첫 화면 출력
	/*
	 먼저 loadPlayers() 통해서 players.txt로부터 Players 로딩
	 1. 새로운 플레이어 등록
	 2. 기존 플레이어로 게임 시작
	 3. 잔고 기준 플레이어 랭킹 출력
	 4. 기존 플레이어 게임머니 충전하기
	 5. 라이센스 출력 혹은 게임방법 출력
	 6. 게임 종료
	 */
	
	bool isRegisteredPlayer(string playerName); // 이미 있는 플레이어 이름인지 반환
	void addNewPlayer(); // #1. 새로운 플레이어 등록
	/*
	 1. 이름 입력
	 2. ->입력한 이름이 이미 있는 이름이면 메뉴 첫화면으로 return
	 3. ->입력한 이름이 없으면 이름 입력 받고 그 이름으로 fillUp() 호출해 게임머니 충전하고 메뉴 첫화면으로 return
	 */
	
	virtual void startGame();    // #2. 기존 플레이어로 게임 시작
	/*
	 이 부분은 BlackJack 클래스의 멤버함수로 함
	 */
	
	void showPlayers();  // #3. 잔고 기준 플레이어 랭킹 출력
	/*
	 벡터로 선언된 Players의 랭킹 출력
	 1. 순번 2. 이름 3. 잔고 4. 승률
	 */
	
	void fillUp(string playerName = "");       // #4. 기존 플레이어 게임머니 충전하기
	/*
	 1. 메뉴 첫 화면에서 들어온 경우 : ->playerName == "" 이다.
		 이름을 입력 받아서 Players에서 검색후 이름이 있으면 충전할 금액 입력받아서 업데이트 하기
									   이름이 없으면 오류 문구 출력하고 메뉴 첫화면으로 return
	 2. 새로운 플레이어 등록에서 들어온 경우 : playerName != "" 이다.
	     충전할 금액 입력 받아서 Players의 end()의 잔고를 업데이트 한 후 메뉴 첫화면으로 return
	 */
	
	void showHowTO();    // #5. 게임방법 및 라이센스 출력
	/*
	 1. 게임방법 출력
	 2. 라이센스 출력
	 */
	
	void exit();         // #6. 게임 종료
	/*
	 1. storePlayers() 통해서 Players를 players.txt 파일에 다시 저장하고
	 2. "Thank you for playing" 출력후
	 3. return
	 */
};

class BlackJack : public Game
{
protected:
	GamePlayer currentPlayer; // 현재 게임하는 사람
	Dealer Computer; // 딜러
	Deck deck; // 총 52장의 카드
	bool turn; // 현재 누구의 턴인가

public:
	BlackJack();
	~BlackJack();
	void initDealer(); // 처음 시작시 딜러 초기화
	void loadPlayer(); // 현재 게임하는 사람 로딩
	
	void shuffleCards(); // 52장의 카드 섞기
	void doBetting(); // 플레이어가 베팅하기
	void getTwoCards(); // 게임 시작시 두 장의 카드 받기
	
	void showPlayerWhatToDo(); // 플레이어가 어떤 일할지 메뉴 출력하기
	/*
	 1. STAY 2. HIT 3. DOUBLEDOWN 4. SURRENDER(2번째부터는 비활성화)
	 */
	void doPlayerTurn(); // 플레이어 턴에 할일 : 블랙잭이나 버스트가 아닐 경우
	void doDealerTurn(); // 딜러 턴에 할 일 : 플레이어가 할일 다 한 경우
	bool compareSum(); // 딜러 카드의 합과 플레이어 카드의 합 비교
	
	void getResult(int result); // 어떤 케이스냐에 따라 처리하는 결과가 달라짐
	/*
	 1 -> 플레이어가 BLACKJACK인 경우 : 베팅금액 + 베팅금액 * 1.5를 돌려받기
	 2 -> 플레이어가 win한 경우 : 베팅금액 + 베팅금액을 돌려받기
	 3 -> push 인 경우 : 베팅금액을 돌려받기
	 4 -> 인슈런스 성공인 경우 : 인슈런스 금액 + 인슈런스 금액 * 2를 돌려받기
	 5 -> 모든 실패의 경우 : 그냥 끝
	 6 -> 플레이어가 SURREND한 경우 : 베팅금액의 1/2를 돌려받기
	
	 */

	virtual void startGame();
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
			 (1) 인슈런스를 한다 -> 인슈런스 금액을 추가적으로 입력받는다.(베팅액의 절반이 상한액이며, Balance에서 뺀다.) -> 플레이어 할일 한다. -> 딜러의 히든카드를 보여준다.
				 (a) 딜러가 블랙잭이다. -> 보험금 + 보험금*2 를 받는다. -> 게임 끝(4)
				 (b) 딜러가 블랙잭이 아니다. -> 보험금은 잃고 딜러가 할일 한다.-> 결과에 따라 계산한다. -> 게임 끝
			 (2) 인슈런스를 하지않는다. -> 플레이어 할일 한다. -> 딜러의 히든카드를 보여준다.
				 (a) 딜러가 블랙잭이다. -> 베팅금액을 잃는다. -> 게임 끝(5)
				 (b) 딜러가 블랙잭이 아니다. -> 딜러가 할일 한다. -> 결과에 따라 계산한다. -> 게임 끝
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
	
	void updatePlayer(); // Players에 이번 플레이어의 정보 업데이트
	void showGameResult(); // 이번 게임 종료시 결과 출력
	/*
	 1. 이름
	 2. 잔고
	 3. 누적 획득 금액 (최종으로 잃었을 경우 -로 표시)
	 5. 랭킹
	 */
};
