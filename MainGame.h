#pragma once
#include "Screen.h"
#include "SceneManager.h"

class MainGame
{
private:
	Screen* screen;

public:
	// ȭ�� �ʱ�ȭ
	void Init();
	// ��� �ݺ��� ����
	void Update();
	// ��� �׸���
	void Render();
	// �޸� ����
	void Release();

public:
	MainGame();
	~MainGame();
};

