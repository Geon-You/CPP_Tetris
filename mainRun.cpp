#include "Include.h"
#include "Screen.h"
#include "MainGame.h"

bool isRun = true;

void main()
{
	// ���� ���� ��ü ����
	MainGame maingame;
	// ���� ���� �� �ʱ�ȭ
	maingame.Init();

	auto updateTime = GetTickCount64();

	while (isRun)
	{
		// ���� �ӵ� ����
		auto t = GetTickCount64();
		if (updateTime + 200 < t)
		{
			updateTime = t;
			// ���� ���� �� ������Ʈ ��� ����
			maingame.Update();
			// ���� ���� �� ������ ��� ����
			maingame.Render();
		}
	}

	// ������ ������ screen �޸� ����
	maingame.Release();
}