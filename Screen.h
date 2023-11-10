#pragma once
#include "Include.h"

class Screen
{
private:
	static HANDLE buffer[2]; // 2개의 출력 버퍼
	// 위의 배열에서 특정 버퍼 접근 시, 사용할 버퍼 배열의 인덱스
	static int bufferIdx;

public:
	void Init();
	void Clear(); // 버퍼 지우기
	void Flip(); // 버퍼 교체
	void Release(); // 버퍼 파괴

public:
	// x, y 좌표로 커서 이동
	static void Goto(int x, int y);
	// x, y 좌표로 이동해서 문자열 출력
	static void Print(const char* str, int x, int y);
	// 출력 글자 색상 설정
	static void SetColor(Color color);

public:
	Screen();
	~Screen();
};
