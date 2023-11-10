#include "Ingame.h"

void Ingame::Init()
{
	// ���� ������ ���� ��ü ���� �� �ʱ�ȭ
	Info mapInfo("Map", 40, 10);
	map = new TetrisMap(mapInfo);

	map->Init();

	// ���� ������ ���� ��ü ���� �� �ʱ�ȭ
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

	// ���� ������ �Ǵ��ϴ� �Լ��� ������ true(���� ����)�̸�
	// GameOver ������ ��ȯ
	if (((CBlocks*)block)->SetGameOver())
		return SceneType::GAMEOVER;

	// �ƴ϶�� ���� �� ����
	return SceneType::NONE;
}

void Ingame::Render()
{
	map->Render();

	block->Render();

	// ���ھ� ���ۿ� ��� ���ڿ� ���
	Screen::Print(scoreBuffer, 80, 25);
}

void Ingame::Release()
{
}

void Ingame::PrintScore()
{
	ZeroMemory(scoreBuffer, sizeof(scoreBuffer)); // ���ھ� ���۸� ���� �ʱ�ȭ
	sprintf_s(scoreBuffer, "Score : %d", ((CBlocks*)block)->score); // ���ھ ĳ�����ؼ� ���

	//scoreStr = to_string( ((CBlocks*)block)->score );
}

Ingame::Ingame()
	: map(nullptr), block(nullptr)
{
}

Ingame::~Ingame()
{
}
