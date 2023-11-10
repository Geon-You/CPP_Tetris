#include "TetrisMap.h"

void TetrisMap::Init()
{
	// �迭�� ���Ҹ� ��� 0���� �ʱ�ȭ(���� �� ����)
	memset(map, 0, sizeof(map[0][0] * MAP_H * MAP_W));

	// ��Ʈ���� ���� �⺻ ���� �׸�

	// 2���� �迭�� ����Ͽ� 0�̸� �� ��, 1�̸� ���� �ٴ��� ǥ���� ����
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

	// ���� ���� �� �׸���
	for (int i = 0; i < MAP_H; ++i)
	{
		for (int j = 0; j < MAP_W; ++j)
		{
			if (map[i][j] == 1)
				Screen::Print("��", info.pos.x + 2 * j, info.pos.y + i);
			else if (map[i][j] == 3)
				Screen::Print("��", info.pos.x + 2 * j, info.pos.y + i);
		}
	}

	// ���� ���� �������� ������� �׸���
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
