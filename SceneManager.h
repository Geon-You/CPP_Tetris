#pragma once
#include "Scene.h"
#include "Include.h"
#include "Title.h"
#include "Ingame.h"
#include "GameOver.h"

class SceneManager
{
public:
	// 현재 씬의 인스턴스를 저장할 멤버 변수
	Scene* currentScene;

public:
	// 현재 씬 반환
	Scene* GetScene();
	// 씬 전환
	void SetScene(SceneType type);

#pragma region 씬 매니저 싱글톤 적용
private:
	// 메모리에 정적으로 올려놓음
	static SceneManager* ins;

private:
	SceneManager();

public:
	~SceneManager();

public:
	// 씬 매니저 인스턴스를 가져오는 함수
	static SceneManager* GetIns()
	{
		// 인스턴스가 없다면 새로 생성
		if (ins == nullptr)
			ins = new SceneManager;

		// 있으면 현재 인스턴스 반환
		return ins;
	}

	// 씬 매니저로 생성된 인스턴스 파괴
	static void Destroy()
	{
		// 인스턴스가 존재한다면 파괴
		if (ins)
		{
			delete ins;
			ins = nullptr;
		}
	}
#pragma endregion
};

