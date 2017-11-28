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
		
		try{
			// 메뉴 선택
			cin>>menu;
			cin.ignore();
			
			if(!isalpha(menu))
				throw menu;
			
			switch (menu) {
				case 'R': // 새로운 플레이어 등록
				case 'r': // 새로운 플레이어 등록
					BJ.addNewPlayer();
					continue;
				case 'G': // 기존 플레이어 시작
				case 'g': // 기존 플레이어 시작
					BJ.startGame();
					continue;
				case 'S': // 플레이어 랭킹 보여주기(잔고순)
				case 's': // 플레이어 랭킹 보여주기(잔고순)
					BJ.showPlayers();
					continue;
				case 'C': // 기존 플레이어 돈 충전하기
				case 'c': // 기존 플레이어 돈 충전하기
					BJ.fillUp();
					continue;
				case 'I':
				case 'i':
					BJ.showHowTO();
					continue;
				case 'E': // 게임 종료하기
				case 'e': // 게임 종료하기
					BJ.exit();
					break;
				default:
					continue;
			}
			break;
		}
		catch(char exception)
		{
			cout<<"Wrong Value."<<endl;
			cin.ignore();
		}
	}
	return 0;
}
