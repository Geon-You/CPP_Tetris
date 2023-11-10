#include "MainGame.h"

void MainGame::Init()
{
	// ȭ���� screen ��ü�� �����ؼ� ���� ���� ������ �� ȭ���� Title�� �� ����
	screen = new Screen;
	// ��ü �ʱ�ȭ
	screen->Init();

	// ���� ȭ���� Title������ ����
	SceneManager::GetIns()->SetScene(SceneType::TITLE);
}

void MainGame::Update()
{
	// ���� ���� Update���� ��ȯ�ް� �ִ� SceneType�� sc�� ����, �̶� auto�� ������ Ÿ�� ���� �� �ص� ��
	auto sc = SceneManager::GetIns()->GetScene()->Update();

	// ���� �� Ÿ���� NONE���� ũ�ٸ� ��, Ÿ��Ʋ���� ������ �����Ϸ��� ���͸� �����ų� �ΰ��ӿ��� �׾��ų� ���ӿ������� ������Ϸ��� ���͸� �����ų� ���
	// ������ Ư�� �ൿ�� �����Ͽ� Update()���� �����ߴٸ� �� ���࿡ �´� ���ο� SceneType�� ��ȯ���� ���̰�,
	// ��ȯ���� �� Ÿ������ ���� ����(����).
	if (sc > SceneType::NONE)
	{
		SceneManager::GetIns()->SetScene(sc);
	}
}

void MainGame::Render()
{
	// ���� �ʱ�ȭ(ȭ���� ������ ����شٴ� �ǹ��� �ʱ�ȭ)
	screen->Clear();

	// ���� ���� Render�� �����ؼ� �׸��� ����
	// ex) Title���� ���� ���, Ingame������ ��, �� ���, GameOver���� ���̵� ���� ���
	// ���ÿ��� ���� ��°� Screen Ŭ������ Print�� �򰥸��� �ȵ�
	SceneManager::GetIns()->GetScene()->Render();

	// �ٸ� ���۷� ��ȯ
	screen->Flip();
}

void MainGame::Release()
{
	// ��ũ�� �ν��Ͻ��� �ʵ忡�� ���������� �޸𸮿� �ִٸ� �ı�
	if (screen)
	{
		delete screen;
		screen = nullptr;
	}

	// �� �Ŵ��� �ı�
	SceneManager::Destroy();
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
