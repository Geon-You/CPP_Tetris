#include "GameOver.h"

void GameOver::Init()
{
}

SceneType GameOver::Update()
{
    // ���� ���������� ����Ű�� ������ �ٽ� �ΰ��� ������ ��ȯ
    if (GetAsyncKeyState(VK_RETURN))
    {
        return SceneType::INGAME;
    }
    // escŰ�� ������ main������ while�� Ż��� ���� ���� ����
    else if (GetAsyncKeyState(VK_ESCAPE))
    {
        isRun = false;
    }

    // �Է��� ���ٸ� ���� �� ����
    return SceneType::NONE;
}

void GameOver::Render()
{
    // ���� ������ �ȳ� ���̵� ���(45, 20�� ��µ�)
    Screen::Print("      �絵�� - Enter                 ���� ���� - ESC      ", 45, 20);
}

void GameOver::Release()
{
}

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
    Release();
}
