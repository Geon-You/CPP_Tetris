#include "Screen.h"

// static �ʵ� �ʱ�ȭ
int Screen::bufferIdx = 0;
HANDLE Screen::buffer[2];

Screen::Screen()
{
	// memset�� �̿��ؼ� �ι�° ���ڰ����� �迭(����) ���� �� �ʱ�ȭ
	memset(buffer, 0, sizeof(buffer));
}

Screen::~Screen()
{
	Release();
}

void Screen::Init()
{
	// �̸� �����ص� ������� ���� ũ�� ����
	COORD size = { BufferSizeX, BufferSizeY };
	// ���۸� ������ ��, ����� �簢�� ������ ����
	SMALL_RECT screen;
	// �簢���� ����, ������, �Ʒ�, �� ������ ����
	screen.Left = 0;
	screen.Right = BufferSizeX - 1;
	screen.Top = 0;
	screen.Bottom = BufferSizeY - 1;

	// Ŀ���� ���� ���� (�Ⱥ��̰Բ�)
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; // Ŀ�� ���� ����
	cursorInfo.bVisible = FALSE; // Ŀ���� ������ �ʰ� ����

	// ���� ���� ���� ���� 2���� ���۸� ����
	for (int i = 0; i < 2; ++i)
	{
		buffer[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(buffer[i], size);
		SetConsoleWindowInfo(buffer[i], TRUE, &screen);
		SetConsoleCursorInfo(buffer[i], &cursorInfo);
	}
}

void Screen::Clear()
{
	// �ֿܼ��� ��� �۾� ��, ���� Ŀ�� ��ġ�� �������� �۾��� ����
	// ȭ�� ��ü�� ������ �� �ְ� ����ϰ� �ִ� Ŀ���� ��ġ�� 0, 0���� ����
	// ����� �۾� ��, ���� ���ڷ� ���� ��ü�� �����
	Goto(0, 0);
	COORD coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(buffer[bufferIdx], ' ', BufferSizeX * BufferSizeY, coord, &dw);
}

void Screen::Flip()
{
	Sleep(10);
	// 2�� ���� �߿� ��¿� ����� ���۸� Ȱ��ȭ
	SetConsoleActiveScreenBuffer(buffer[bufferIdx]);
	// idx ��° ���۸� Ȱ��ȭ ��������, ���� �ε����� ����
	bufferIdx = !bufferIdx; // 0, 1, 0, 1 �������� �����Ǹ鼭 ���۰� �ٲ�
}

void Screen::Release()
{
}

void Screen::Goto(int x, int y)
{
	COORD pos = { x, y };
	// Ŀ���� x, y ��ǥ�� �̵�
	SetConsoleCursorPosition(buffer[bufferIdx], pos);
}

void Screen::Print(const char* str, int x, int y)
{
	Goto(x, y);
	DWORD dw;
	// ����[�����ε���]�� �ι�° ���ڷ� ���� ���ڿ��� ���
	WriteFile(buffer[bufferIdx], str, strlen(str), &dw, NULL);
}

void Screen::SetColor(Color color)
{
	// ��Ʈ ���� ����
	SetConsoleTextAttribute(buffer[bufferIdx], (unsigned short)color);
}
