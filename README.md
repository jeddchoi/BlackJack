# BlackJack
c++ blackjack project

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
		(2) 딜러는 블랙잭이 아니다 -> 딜러가 할일한다. -> 결과에 따라 계산한다. -> 게임 끝
	2) 플레이어가 블랙잭이 아니다.
		(1) 플레이어가 할일 한후
			(a) 결과가 1인 경우
				> 딜러는 블랙잭이다.(21) -> 딜러가 이겼다. -> 게임 끝
				> 딜러가 블랙잭이 아니다.
					> 딜러가 할일 한후 ->  결과에 따라 처리 -> 게임 끝
			(b) 결과가 5혹은 6인 경우 -> 게임 종료(5)
			

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
