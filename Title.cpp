#include "Title.h"

void Title::Init()
{
}

SceneType Title::Update()
{
	// 유저가 엔터를 입력하면 인게임 씬 실행, 즉, 타이틀에서 인게임으로 화면 전환
	if (GetAsyncKeyState(VK_RETURN))
		return SceneType::INGAME;

	// 입력이 없다면 현재 씬 유지
	return SceneType::NONE;
}

void Title::Render()
{
	Screen::SetColor(Color::Red);
	// 제목 출력(70, 22부터 가로로 출력함)
	Screen::Print("T", 70, 22);
	Screen::SetColor(Color::Blue);
	Screen::Print("E", 72, 22);
	Screen::SetColor(Color::Yellow);
	Screen::Print("T", 74, 22);
	Screen::SetColor(Color::Green);
	Screen::Print("R", 76, 22);
	Screen::SetColor(Color::BlueGreen);
	Screen::Print("I", 78, 22);
	Screen::SetColor(Color::Purple);
	Screen::Print("S", 80, 22);
	Screen::SetColor(Color::White);
}

void Title::Release()
{
}

Title::Title()
{
}

Title::~Title()
{
}
