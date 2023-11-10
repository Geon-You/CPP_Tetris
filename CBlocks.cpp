#include "CBlocks.h"

void CBlocks::Init()
{
	memset(shape, 0, sizeof(4 * 4 * 4)); // 블럭 모양 배열 초기화

	rotateNumber = 0; // 회전 번호는 0부터 시작
	srand((unsigned int)time(NULL));
	score = 0; // 점수를 나타내는 멤버 변수 초기화

	rotCooltime = GetTickCount();

	canCreateBlock = true; // 블럭이 땅에 닿아야지만 새로 블럭을 만드는데 이를 제어하는 bool 변수

	startPosX = info.pos.x; // 블럭이 내려오는 처음 위치를 저장
	startPosY = info.pos.y; // 블럭이 내려오는 처음 위치를 저장
	memcpy(mapCopy, map->map, sizeof(int) * MAP_H * MAP_W); // TetrisMap.cpp에 있는 map 배열의 데이터 복사
	
	// 초기에 7가지 랜덤한 모양의 블럭을 담을 리스트 생성
	for (int i = 0; i < 7; ++i)
		nextShapes.push_back(rand() % 7 + 1);
}

SceneType CBlocks::Update()
{
	if (SetGameOver())
		return SceneType::GAMEOVER; // 게임 오버 조건이 실행되면 게임 오버 씬을 불러옴

	// 회전 쿨타임 처리
	auto t = GetTickCount();
	if (isRot && rotCooltime + 500 < t)
	{
		rotCooltime = t;
		isRot = false;
	}

	// 블럭이 땅에 닿아 굳어지고 나서 블록 생성
	if (canCreateBlock)
	{
		CreateBlock();
		canCreateBlock = false;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!CheckCollision(info.pos.x - 2, info.pos.y))
		{
			// 화살표 방향키 왼쪽 누르면 블럭 왼쪽으로 이동(벽과 충돌하지 않을 때)
			info.pos.x -= 2;
		}
	}

	// 여기서부턴 블럭 이동, 회전 처리
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!CheckCollision(info.pos.x + 2, info.pos.y))
		{
			// 화살표 방향키 오른쪽 누르면 블럭 오른쪽으로 이동
			info.pos.x += 2;
		}
	}

	if (GetAsyncKeyState(VK_SPACE) && !isRot)
	{
		bool isLeftColl = CheckLeft(info.pos.x, info.pos.y);

		if (isLeftColl)
		{
			info.pos.x += 2;
		}
		else if (CheckRight(info.pos.x, info.pos.y))
		{
			info.pos.x -= 2;
		}

		rotate();
	}

	bool isBot = CheckBottom(info.pos.x, info.pos.y);

	if (!isBot)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			// 화살표 방향키 아래쪽 누르면 빠르게 하강
			info.pos.y += 2;
		}
		else
		{
			// 블럭이 내려오고 sleepTime(블럭이 내려오는 속도를 조절하는 값)만큼 콘솔 딜레이
			info.pos.y += 1;
		}
	}
	else if (isBot)
	{
		info.pos.y = info.pos.y;
		// 바닥이나 블럭인지를 판단하여 닿으면 그 자리로 블럭을 굳혀버림
		BlockTouchBottom(info.pos.x, info.pos.y);
		// 맵을 순회하면서 완성된 줄이 있다면 삭제
		DeleteLine();
	}

	return SceneType::NONE;
}

void CBlocks::Render()
{
	// 블럭 그리기
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (shape[rotateNumber][i][j] == 2)
				Screen::Print("□", info.pos.x + 2 * j, info.pos.y + i);
		}
	}

	// 쌓여서 굳어진 블럭 그리기
	Screen::SetColor(Color::Green);

	for (int i = 0; i < MAP_H; ++i)
	{
		for (int j = 0; j < MAP_W; ++j)
		{
			if (mapCopy[i][j] == 4)
				Screen::Print("▣", map->GetInfo().pos.x + 2 * j, map->GetInfo().pos.y + i);
		}
	}
	Screen::SetColor(Color::White);

	// 다음에 나올 블럭 그리기
	Screen::SetColor(Color::Yellow);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (nextShape[0][i][j] == 2)
				Screen::Print("▣", 80 + 2 * i, 15 + j);
		}
	}
	Screen::SetColor(Color::White);
}

void CBlocks::Release()
{
}

void CBlocks::rotate()
{
	isRot = true;
	// 회전 번호인 0, 1, 2, 3을 반복
	rotateNumber = (rotateNumber + 1) % 4;
}

// 벽에 닿았는 지 검사하는 메서드. 블럭이 좌우 벽을 뚫고 나가지 않게 제어해줌
bool CBlocks::CheckCollision(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[rotateNumber][i][j] == 2)
			{
				// 맵의 생성위치는 40, 10이고 블럭의 생성 위치는 52, 8이다. 서로 좌표가 다르고 인덱스 개수도 다르니
				// 이걸 맞춰줄 연산이 필요하다. 그렇지 않으면 좌표가 다르니 그 위치의 맵 인덱스를 인식하지 못한다. 엉뚱한 인덱스를 비교한다.
				int blockX = (x - 40) / 2;
				int blockY = (y - 10);
				if (mapCopy[blockY + i][blockX + j] == 1 || mapCopy[blockY + i][blockX + j] == 4)
					return true;
			}
		}
	}

	return false;
}

// 바닥에 닿았는지 검사해주는 메서드. 바닥이나 굳어진 블럭에 닿았다면 true를 반환해서 닿았다는 것을 알려줌
bool CBlocks::CheckBottom(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[rotateNumber][i][j] == 2)
			{
				// 바로 아래를 검사할 것이니, 연산을 통해 좌표를 맞춰준 다음에 y에 1을 더해 아래쪽 충돌을 검사한다.
				int blockX = (x - 40) / 2;
				int blockY = (y - 10) + 1;

				// 바닥이나 쌓여진 블럭에 닿았다면 true를 반환해서 다른 함수에서 블럭을 굳힐 수 있도록 한다.
				if (mapCopy[blockY + i][blockX + j] == 3 || mapCopy[blockY + i][blockX + j] == 4)
					return true;
			}
		}
	}

	return false;
}

// 블럭이 땅에 닿았다면 다시 새로운 블럭을 생성해 줄 메서드
// 다음에 나올 블럭 모양 처리도 여기서 실행
void CBlocks::CreateBlock()
{
	rotateNumber = 0;
	auto block = nextShapes.front();

	// 다음에 나올 블럭 모양에 접근
	auto iter = nextShapes.begin();
	advance(iter, 1);

	auto nextBlock = *iter;

	// switch문을 통해 랜덤하게 선택된 블럭 배열을 복사해서 출력할 계획이다.
	switch (block)
	{
	case 1:
		memcpy(shape, block1, sizeof(int) * 4 * 4 * 4);
		break;
	case 2:
		memcpy(shape, block2, sizeof(int) * 4 * 4 * 4);
		break;
	case 3:
		memcpy(shape, block3, sizeof(int) * 4 * 4 * 4);
		break;
	case 4:
		memcpy(shape, block4, sizeof(int) * 4 * 4 * 4);
		break;
	case 5:
		memcpy(shape, block5, sizeof(int) * 4 * 4 * 4);
		break;
	case 6:
		memcpy(shape, block6, sizeof(int) * 4 * 4 * 4);
		break;
	case 7:
		memcpy(shape, block7, sizeof(int) * 4 * 4 * 4);
		break;
	}

	// 다음에 나올 블럭 모양 배열로 복사
	switch (nextBlock)
	{
	case 1:
		memcpy(nextShape, block1, sizeof(int) * 4 * 4 * 4);
		break;
	case 2:
		memcpy(nextShape, block2, sizeof(int) * 4 * 4 * 4);
		break;
	case 3:
		memcpy(nextShape, block3, sizeof(int) * 4 * 4 * 4);
		break;
	case 4:
		memcpy(nextShape, block4, sizeof(int) * 4 * 4 * 4);
		break;
	case 5:
		memcpy(nextShape, block5, sizeof(int) * 4 * 4 * 4);
		break;
	case 6:
		memcpy(nextShape, block6, sizeof(int) * 4 * 4 * 4);
		break;
	case 7:
		memcpy(nextShape, block7, sizeof(int) * 4 * 4 * 4);
		break;
	}

	nextShapes.pop_front(); // 제일 앞에 있는(제일 첫 번째로 생성된) 모양을 사용이 끝났으니 삭제
	nextShapes.push_back(rand() % 7 + 1); // 계속 랜덤한 블럭을 뽑아서 리스트에 넣음
}

// 블럭이 땅이나 굳은 블럭에 닿았다면 그 자리에 블럭을 쌓는 메서드
void CBlocks::BlockTouchBottom(int x, int y)
{
	// 바닥이나 굳은 블럭에 닿았는지 검사
	if (CheckBottom(x, y))
	{
		// 바닥이나 블럭에 닿았다면 안착한 블럭들을 맵 위치에 저장
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shape[rotateNumber][i][j] == 2)
				{
					int blockX = (x - 40) / 2;
					int blockY = (y - 10);

					// 그 위치에 4로 저장 (굳은 블럭은 4로 표현)
					mapCopy[i + blockY][j + blockX] = 4;
				}
			}
		}
		// 그 위치에 저장했다면 블럭의 모양을 담고있던 shape 배열을 초기화시켜
		// 화면상에서 없애도록(출력이 안 되게끔) 한다.
		memset(shape, 0, sizeof(int) * 4 * 4 * 4);

		// 블럭이 쌓였다면 다시 생성될 블럭의 위치를 원래 생성 위치로 되돌린다.
		info.pos.x = startPosX;
		info.pos.y = startPosY;
		canCreateBlock = true;
	}
}

// 블럭을 쌓을때마다 mapCopy를 순회하며 한 줄이 완성됐다면 그 줄을 삭제하는 메서드
// 동시에 여러줄이 완성됐을 때도 한꺼번에 삭제 가능
void CBlocks::DeleteLine()
{
	int deleteLine = 0;

	for (int i = MAP_H - 2; i >= 1; )
	{
		bool lineClear = true;

		for (int j = 1; j < MAP_W - 1; j++)
		{
			if (mapCopy[i][j] != 4)
			{
				lineClear = false;
				break;
			}
		}

		if (lineClear) // 줄이 꽉 찼다면
		{
			for (int j = i; j > 0; j--)
			{
				for (int k = 1; k < MAP_W - 1; k++)
				{
					mapCopy[j][k] = mapCopy[j - 1][k];
				}
			}
			++deleteLine; // 삭제된 줄 개수 카운트 증가
		}
		else
		{
			--i;
		}
	}

	this->score += deleteLine * 100; // 삭제된 줄 개수 카운트에 따라 스코어 합산
}

// 회전해서 다음에 나올 모양이 왼쪽 벽을 뚫고 나가는지(충돌하는지) 체크하는 메서드
bool CBlocks::CheckLeft(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[(rotateNumber + 1) % 4][i][j] == 2)
			{
				int blockX = ((x - 40) / 2) - 1; // 한 칸 왼쪽 체크
				int blockY = (y - 10);
				if (mapCopy[blockY + i][blockX + j] == 1)
					return true;
			}
		}
	}

	return false;
}

// 마찬가지로 오른쪽을 체크하는 메서드
bool CBlocks::CheckRight(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[(rotateNumber + 1) % 4][i][j] == 2)
			{
				int blockX = ((x - 40) / 2) + 1; // 한 칸 오른쪽 체크
				int blockY = (y - 10);
				if (mapCopy[blockY + i][blockX + j] == 1)
					return true;
			}
		}
	}

	return false;
}

// 게임 오버를 체크하는 메서드
bool CBlocks::SetGameOver()
{
	for (int j = 0; j < MAP_W; ++j)
	{
		if (mapCopy[0][j] == 4) // 맨 윗줄에 블럭이 쌓인다면 (쌓인 블럭은 4로 처리하기로 했었음)
			return true; // 게임 오버
	}

	return false; // 아직 게임 오버 아님
}

CBlocks::CBlocks(Info info)
	: Obj(info)
{
}

CBlocks::~CBlocks()
{
}
