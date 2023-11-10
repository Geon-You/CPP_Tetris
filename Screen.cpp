#include "Screen.h"

// static 필드 초기화
int Screen::bufferIdx = 0;
HANDLE Screen::buffer[2];

Screen::Screen()
{
	// memset을 이용해서 두번째 인자값으로 배열(버퍼) 원소 값 초기화
	memset(buffer, 0, sizeof(buffer));
}

Screen::~Screen()
{
	Release();
}

void Screen::Init()
{
	// 미리 정의해둔 사이즈로 버퍼 크기 결정
	COORD size = { BufferSizeX, BufferSizeY };
	// 버퍼를 생성할 때, 사용할 사각형 영역을 설정
	SMALL_RECT screen;
	// 사각형의 왼쪽, 오른쪽, 아래, 위 사이즈 지정
	screen.Left = 0;
	screen.Right = BufferSizeX - 1;
	screen.Top = 0;
	screen.Bottom = BufferSizeY - 1;

	// 커서에 관한 설정 (안보이게끔)
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; // 커서 굵기 설정
	cursorInfo.bVisible = FALSE; // 커서를 보이지 않게 설정

	// 위의 설정 값에 따라 2개의 버퍼를 생성
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
	// 콘솔에서 출력 작업 시, 현재 커서 위치를 기준으로 작업을 실행
	// 화면 전체가 지워질 수 있게 사용하고 있던 커서의 위치를 0, 0으로 변경
	// 지우는 작업 시, 공백 문자로 버퍼 전체를 덮어쓰기
	Goto(0, 0);
	COORD coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(buffer[bufferIdx], ' ', BufferSizeX * BufferSizeY, coord, &dw);
}

void Screen::Flip()
{
	Sleep(10);
	// 2개 버퍼 중에 출력에 사용할 버퍼를 활성화
	SetConsoleActiveScreenBuffer(buffer[bufferIdx]);
	// idx 번째 버퍼를 활성화 시켰으니, 버퍼 인덱스를 변경
	bufferIdx = !bufferIdx; // 0, 1, 0, 1 형식으로 반전되면서 버퍼가 바뀜
}

void Screen::Release()
{
}

void Screen::Goto(int x, int y)
{
	COORD pos = { x, y };
	// 커서를 x, y 좌표로 이동
	SetConsoleCursorPosition(buffer[bufferIdx], pos);
}

void Screen::Print(const char* str, int x, int y)
{
	Goto(x, y);
	DWORD dw;
	// 버퍼[버퍼인덱스]에 두번째 인자로 받은 문자열을 출력
	WriteFile(buffer[bufferIdx], str, strlen(str), &dw, NULL);
}

void Screen::SetColor(Color color)
{
	// 폰트 색깔 설정
	SetConsoleTextAttribute(buffer[bufferIdx], (unsigned short)color);
}
