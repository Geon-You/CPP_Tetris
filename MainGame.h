#pragma once
#include "Screen.h"
#include "SceneManager.h"

class MainGame
{
private:
	Screen* screen;

public:
	// 화면 초기화
	void Init();
	// 계속 반복할 동작
	void Update();
	// 계속 그리기
	void Render();
	// 메모리 해제
	void Release();

public:
	MainGame();
	~MainGame();
};

