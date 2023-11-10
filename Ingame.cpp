#include "Ingame.h"

void Ingame::Init()
{
	// 맵의 정보를 가진 객체 생성 후 초기화
	Info mapInfo("Map", 40, 10);
	map = new TetrisMap(mapInfo);

	map->Init();

	// 블럭의 정보를 가진 객체 생성 후 초기화
	Info blockInfo("Block", 54 - 4, 8);
	block = new CBlocks(blockInfo);

	((CBlocks*)block)->SetMap((TetrisMap*)map);
	block->Init();
}

SceneType Ingame::Update()
{
	map->Update();

	block->Update();

	PrintScore();

	// 게임 오버를 판단하는 함수를 실행해 true(게임 오버)이면
	// GameOver 씬으로 전환
	if (((CBlocks*)block)->SetGameOver())
		return SceneType::GAMEOVER;

	// 아니라면 현재 씬 유지
	return SceneType::NONE;
}

void Ingame::Render()
{
	map->Render();

	block->Render();

	// 스코어 버퍼에 담긴 문자열 출력
	Screen::Print(scoreBuffer, 80, 25);
}

void Ingame::Release()
{
}

void Ingame::PrintScore()
{
	ZeroMemory(scoreBuffer, sizeof(scoreBuffer)); // 스코어 버퍼를 먼저 초기화
	sprintf_s(scoreBuffer, "Score : %d", ((CBlocks*)block)->score); // 스코어를 캐스팅해서 사용

	//scoreStr = to_string( ((CBlocks*)block)->score );
}

Ingame::Ingame()
	: map(nullptr), block(nullptr)
{
}

Ingame::~Ingame()
{
}
