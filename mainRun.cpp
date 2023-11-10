#include "Include.h"
#include "Screen.h"
#include "MainGame.h"

bool isRun = true;

void main()
{
	// 메인 게임 객체 생성
	MainGame maingame;
	// 게임 시작 전 초기화
	maingame.Init();

	auto updateTime = GetTickCount64();

	while (isRun)
	{
		// 게임 속도 조절
		auto t = GetTickCount64();
		if (updateTime + 200 < t)
		{
			updateTime = t;
			// 게임 진행 중 업데이트 계속 실행
			maingame.Update();
			// 게임 진행 중 렌더링 계속 실행
			maingame.Render();
		}
	}

	// 게임이 끝나고 screen 메모리 해제
	maingame.Release();
}