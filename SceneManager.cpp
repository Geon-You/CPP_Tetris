#include "SceneManager.h"

// ���� �ʵ� �ʱ�ȭ
SceneManager* SceneManager::ins = nullptr;

Scene* SceneManager::GetScene()
{
	// ���� �� ��ȯ
	return currentScene;
}

void SceneManager::SetScene(SceneType type)
{
	// �̹� ���� ���� �����Ѵٸ� �̹� �����ϰ� �ִ� �� �ı�
	if (currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
	}

	// ����ġ���� ���� ���ο� �� ����
	switch (type)
	{
	case TITLE:
		currentScene = new Title();
		break;
	case INGAME:
		currentScene = new Ingame();
		break;
	case GAMEOVER:
		currentScene = new GameOver();
		break;
	}

	// ���� ������ ���ο� ������ ����� �� �ʱ�ȭ
	currentScene->Init();
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	// �� �ʵ� �޸� ����
	if (currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}
