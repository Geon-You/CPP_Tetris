#pragma once
#include "Include.h"

class Screen
{
private:
	static HANDLE buffer[2]; // 2���� ��� ����
	// ���� �迭���� Ư�� ���� ���� ��, ����� ���� �迭�� �ε���
	static int bufferIdx;

public:
	void Init();
	void Clear(); // ���� �����
	void Flip(); // ���� ��ü
	void Release(); // ���� �ı�

public:
	// x, y ��ǥ�� Ŀ�� �̵�
	static void Goto(int x, int y);
	// x, y ��ǥ�� �̵��ؼ� ���ڿ� ���
	static void Print(const char* str, int x, int y);
	// ��� ���� ���� ����
	static void SetColor(Color color);

public:
	Screen();
	~Screen();
};
