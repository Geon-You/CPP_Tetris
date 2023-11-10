#include "SceneManager.h"

// 정적 필드 초기화
SceneManager* SceneManager::ins = nullptr;

Scene* SceneManager::GetScene()
{
	// 현재 씬 반환
	return currentScene;
}

void SceneManager::SetScene(SceneType type)
{
	// 이미 현재 씬이 존재한다면 이미 존재하고 있는 씬 파괴
	if (currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
	}

	// 스위치문을 통해 새로운 씬 생성
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

	// 이전 씬에서 새로운 씬으로 변경될 때 초기화
	currentScene->Init();
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	// 씬 필드 메모리 해제
	if (currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}
