#pragma once
#include "Scene.h"
#include "Include.h"
#include "Title.h"
#include "Ingame.h"
#include "GameOver.h"

class SceneManager
{
public:
	// ���� ���� �ν��Ͻ��� ������ ��� ����
	Scene* currentScene;

public:
	// ���� �� ��ȯ
	Scene* GetScene();
	// �� ��ȯ
	void SetScene(SceneType type);

#pragma region �� �Ŵ��� �̱��� ����
private:
	// �޸𸮿� �������� �÷�����
	static SceneManager* ins;

private:
	SceneManager();

public:
	~SceneManager();

public:
	// �� �Ŵ��� �ν��Ͻ��� �������� �Լ�
	static SceneManager* GetIns()
	{
		// �ν��Ͻ��� ���ٸ� ���� ����
		if (ins == nullptr)
			ins = new SceneManager;

		// ������ ���� �ν��Ͻ� ��ȯ
		return ins;
	}

	// �� �Ŵ����� ������ �ν��Ͻ� �ı�
	static void Destroy()
	{
		// �ν��Ͻ��� �����Ѵٸ� �ı�
		if (ins)
		{
			delete ins;
			ins = nullptr;
		}
	}
#pragma endregion
};

