#include "TetrisMap.h"

void TetrisMap::Init()
{
	// 배열의 원소를 모두 0으로 초기화(전부 빈 공간)
	memset(map, 0, sizeof(map[0][0] * MAP_H * MAP_W));

	// 테트리스 판의 기본 맵을 그림

	// 2차원 배열을 사용하여 0이면 빈 곳, 1이면 벽과 바닥을 표현할 예정
	for (int i = 0; i < MAP_H; ++i)
	{
		for (int j = 0; j < MAP_W; ++j)
		{
			map[i][j] = 0;
		}

		map[i][0] = 1;
		map[i][MAP_W - 1] = 1;
	}

	for (int j = 0; j < MAP_W; ++j)
	{
		map[MAP_H - 1][j] = 3;
	}
}

SceneType TetrisMap::Update()
{
	return SceneType::NONE;
}

void TetrisMap::Render()
{
	Screen::SetColor(Color::SkyBlue);

	// 블럭을 쌓을 맵 그리기
	for (int i = 0; i < MAP_H; ++i)
	{
		for (int j = 0; j < MAP_W; ++j)
		{
			if (map[i][j] == 1)
				Screen::Print("■", info.pos.x + 2 * j, info.pos.y + i);
			else if (map[i][j] == 3)
				Screen::Print("□", info.pos.x + 2 * j, info.pos.y + i);
		}
	}

	// 게임 오버 기준점인 데드라인 그리기
	Screen::SetColor(Color::Red);
	for (int j = 1; j < MAP_W - 1; ++j)
	{
		if (map[0][j] == 0)
			Screen::Print("--", info.pos.x + 2 * j, info.pos.y);
	}
	Screen::SetColor(Color::White);
}

void TetrisMap::Release()
{
}

TetrisMap::TetrisMap()
{
}

TetrisMap::TetrisMap(Info info)
	: Obj(info)
{
}

TetrisMap::~TetrisMap()
{
	Release();
}
