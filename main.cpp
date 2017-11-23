//
//  main.cpp
//  cppterm
//
//  Created by Gwang Young Choi on 2017. 11. 14..
//  Copyright © 2017년 Gwang Young Choe. All rights reserved.
//

#include <iostream>
#include "Game.h"
#include "Card.h"
#include "Player.h"


/*
 여유 있으면 split도 구현
 승률도 표시하기
 덱 수를 여러개 랜덤으로 결정

 */

int main()
{
	BlackJack BJ;
	char menu;
	
	while(1)
	{
		// 메뉴 첫화면 출력
		BJ.showIntro();
		
		// 메뉴 선택
		cin>>menu;
		
		switch (menu) {
			case 1: // 새로운 플레이어 등록
				BJ.addNewPlayer();
				continue;
			case 2: // 기존 플레이어 시작
				BJ.startGame();
				continue;
			case 3: // 플레이어 랭킹 보여주기(잔고순)
				BJ.showPlayers();
				continue;
			case 4: // 기존 플레이어 돈 충전하기
				BJ.fillUp();
				continue;
			case 5:
				BJ.showHowTO();
				continue;
			case 6: // 게임 종료하기 
				BJ.exit();
				break;
			default:
				continue;
		}
		break;
	}
	return 0;
}
