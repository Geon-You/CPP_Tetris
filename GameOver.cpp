#include "GameOver.h"

void GameOver::Init()
{
}

SceneType GameOver::Update()
{
    // 게임 오버씬에서 엔터키를 누르면 다시 인게임 씬으로 전환
    if (GetAsyncKeyState(VK_RETURN))
    {
        return SceneType::INGAME;
    }
    // esc키를 누르면 main에서의 while문 탈출로 인해 게임 종료
    else if (GetAsyncKeyState(VK_ESCAPE))
    {
        isRun = false;
    }

    // 입력이 없다면 지금 씬 유지
    return SceneType::NONE;
}

void GameOver::Render()
{
    // 게임 오버시 안내 가이드 출력(45, 20에 출력됨)
    Screen::Print("      재도전 - Enter                 게임 종료 - ESC      ", 45, 20);
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
