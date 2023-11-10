#include "Title.h"

void Title::Init()
{
}

SceneType Title::Update()
{
	// ������ ���͸� �Է��ϸ� �ΰ��� �� ����, ��, Ÿ��Ʋ���� �ΰ������� ȭ�� ��ȯ
	if (GetAsyncKeyState(VK_RETURN))
		return SceneType::INGAME;

	// �Է��� ���ٸ� ���� �� ����
	return SceneType::NONE;
}

void Title::Render()
{
	Screen::SetColor(Color::Red);
	// ���� ���(70, 22���� ���η� �����)
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
