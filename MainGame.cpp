#include "MainGame.h"

void MainGame::Init()
{
	// 화면인 screen 객체를 생성해서 제일 먼저 유저가 볼 화면인 Title로 씬 설정
	screen = new Screen;
	// 객체 초기화
	screen->Init();

	// 시작 화면을 Title씬으로 설정
	SceneManager::GetIns()->SetScene(SceneType::TITLE);
}

void MainGame::Update()
{
	// 현재 씬의 Update에서 반환받고 있는 SceneType을 sc로 저장, 이때 auto로 받으니 타입 지정 안 해도 됨
	auto sc = SceneManager::GetIns()->GetScene()->Update();

	// 현재 씬 타입이 NONE보다 크다면 즉, 타이틀에서 게임을 시작하려고 엔터를 누르거나 인게임에서 죽었거나 게임오버에서 재시작하려고 엔터를 눌렀거나 등등
	// 씬에서 특정 행동을 수행하여 Update()에서 감지했다면 그 수행에 맞는 새로운 SceneType을 반환해줄 것이고,
	// 반환받은 씬 타입으로 씬을 세팅(설정).
	if (sc > SceneType::NONE)
	{
		SceneManager::GetIns()->SetScene(sc);
	}
}

void MainGame::Render()
{
	// 버퍼 초기화(화면의 내용을 비워준다는 의미의 초기화)
	screen->Clear();

	// 현재 씬의 Render를 실행해서 그리기 수행
	// ex) Title씬의 제목 출력, Ingame씬에서 블럭, 맵 출력, GameOver씬의 가이드 문구 출력
	// 예시에서 말한 출력과 Screen 클래스의 Print와 헷갈리면 안됨
	SceneManager::GetIns()->GetScene()->Render();

	// 다른 버퍼로 교환
	screen->Flip();
}

void MainGame::Release()
{
	// 스크린 인스턴스를 필드에서 선언했으니 메모리에 있다면 파괴
	if (screen)
	{
		delete screen;
		screen = nullptr;
	}

	// 씬 매니저 파괴
	SceneManager::Destroy();
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
