#include "CBlocks.h"

void CBlocks::Init()
{
	memset(shape, 0, sizeof(4 * 4 * 4)); // �� ��� �迭 �ʱ�ȭ

	rotateNumber = 0; // ȸ�� ��ȣ�� 0���� ����
	srand((unsigned int)time(NULL));
	score = 0; // ������ ��Ÿ���� ��� ���� �ʱ�ȭ

	rotCooltime = GetTickCount();

	canCreateBlock = true; // ���� ���� ��ƾ����� ���� ���� ����µ� �̸� �����ϴ� bool ����

	startPosX = info.pos.x; // ���� �������� ó�� ��ġ�� ����
	startPosY = info.pos.y; // ���� �������� ó�� ��ġ�� ����
	memcpy(mapCopy, map->map, sizeof(int) * MAP_H * MAP_W); // TetrisMap.cpp�� �ִ� map �迭�� ������ ����
	
	// �ʱ⿡ 7���� ������ ����� ���� ���� ����Ʈ ����
	for (int i = 0; i < 7; ++i)
		nextShapes.push_back(rand() % 7 + 1);
}

SceneType CBlocks::Update()
{
	if (SetGameOver())
		return SceneType::GAMEOVER; // ���� ���� ������ ����Ǹ� ���� ���� ���� �ҷ���

	// ȸ�� ��Ÿ�� ó��
	auto t = GetTickCount();
	if (isRot && rotCooltime + 500 < t)
	{
		rotCooltime = t;
		isRot = false;
	}

	// ���� ���� ��� �������� ���� ��� ����
	if (canCreateBlock)
	{
		CreateBlock();
		canCreateBlock = false;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!CheckCollision(info.pos.x - 2, info.pos.y))
		{
			// ȭ��ǥ ����Ű ���� ������ �� �������� �̵�(���� �浹���� ���� ��)
			info.pos.x -= 2;
		}
	}

	// ���⼭���� �� �̵�, ȸ�� ó��
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!CheckCollision(info.pos.x + 2, info.pos.y))
		{
			// ȭ��ǥ ����Ű ������ ������ �� ���������� �̵�
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
			// ȭ��ǥ ����Ű �Ʒ��� ������ ������ �ϰ�
			info.pos.y += 2;
		}
		else
		{
			// ���� �������� sleepTime(���� �������� �ӵ��� �����ϴ� ��)��ŭ �ܼ� ������
			info.pos.y += 1;
		}
	}
	else if (isBot)
	{
		info.pos.y = info.pos.y;
		// �ٴ��̳� �������� �Ǵ��Ͽ� ������ �� �ڸ��� ���� ��������
		BlockTouchBottom(info.pos.x, info.pos.y);
		// ���� ��ȸ�ϸ鼭 �ϼ��� ���� �ִٸ� ����
		DeleteLine();
	}

	return SceneType::NONE;
}

void CBlocks::Render()
{
	// �� �׸���
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (shape[rotateNumber][i][j] == 2)
				Screen::Print("��", info.pos.x + 2 * j, info.pos.y + i);
		}
	}

	// �׿��� ������ �� �׸���
	Screen::SetColor(Color::Green);

	for (int i = 0; i < MAP_H; ++i)
	{
		for (int j = 0; j < MAP_W; ++j)
		{
			if (mapCopy[i][j] == 4)
				Screen::Print("��", map->GetInfo().pos.x + 2 * j, map->GetInfo().pos.y + i);
		}
	}
	Screen::SetColor(Color::White);

	// ������ ���� �� �׸���
	Screen::SetColor(Color::Yellow);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (nextShape[0][i][j] == 2)
				Screen::Print("��", 80 + 2 * i, 15 + j);
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
	// ȸ�� ��ȣ�� 0, 1, 2, 3�� �ݺ�
	rotateNumber = (rotateNumber + 1) % 4;
}

// ���� ��Ҵ� �� �˻��ϴ� �޼���. ���� �¿� ���� �հ� ������ �ʰ� ��������
bool CBlocks::CheckCollision(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[rotateNumber][i][j] == 2)
			{
				// ���� ������ġ�� 40, 10�̰� ���� ���� ��ġ�� 52, 8�̴�. ���� ��ǥ�� �ٸ��� �ε��� ������ �ٸ���
				// �̰� ������ ������ �ʿ��ϴ�. �׷��� ������ ��ǥ�� �ٸ��� �� ��ġ�� �� �ε����� �ν����� ���Ѵ�. ������ �ε����� ���Ѵ�.
				int blockX = (x - 40) / 2;
				int blockY = (y - 10);
				if (mapCopy[blockY + i][blockX + j] == 1 || mapCopy[blockY + i][blockX + j] == 4)
					return true;
			}
		}
	}

	return false;
}

// �ٴڿ� ��Ҵ��� �˻����ִ� �޼���. �ٴ��̳� ������ ���� ��Ҵٸ� true�� ��ȯ�ؼ� ��Ҵٴ� ���� �˷���
bool CBlocks::CheckBottom(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[rotateNumber][i][j] == 2)
			{
				// �ٷ� �Ʒ��� �˻��� ���̴�, ������ ���� ��ǥ�� ������ ������ y�� 1�� ���� �Ʒ��� �浹�� �˻��Ѵ�.
				int blockX = (x - 40) / 2;
				int blockY = (y - 10) + 1;

				// �ٴ��̳� �׿��� ���� ��Ҵٸ� true�� ��ȯ�ؼ� �ٸ� �Լ����� ���� ���� �� �ֵ��� �Ѵ�.
				if (mapCopy[blockY + i][blockX + j] == 3 || mapCopy[blockY + i][blockX + j] == 4)
					return true;
			}
		}
	}

	return false;
}

// ���� ���� ��Ҵٸ� �ٽ� ���ο� ���� ������ �� �޼���
// ������ ���� �� ��� ó���� ���⼭ ����
void CBlocks::CreateBlock()
{
	rotateNumber = 0;
	auto block = nextShapes.front();

	// ������ ���� �� ��翡 ����
	auto iter = nextShapes.begin();
	advance(iter, 1);

	auto nextBlock = *iter;

	// switch���� ���� �����ϰ� ���õ� �� �迭�� �����ؼ� ����� ��ȹ�̴�.
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

	// ������ ���� �� ��� �迭�� ����
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

	nextShapes.pop_front(); // ���� �տ� �ִ�(���� ù ��°�� ������) ����� ����� �������� ����
	nextShapes.push_back(rand() % 7 + 1); // ��� ������ ���� �̾Ƽ� ����Ʈ�� ����
}

// ���� ���̳� ���� ���� ��Ҵٸ� �� �ڸ��� ���� �״� �޼���
void CBlocks::BlockTouchBottom(int x, int y)
{
	// �ٴ��̳� ���� ���� ��Ҵ��� �˻�
	if (CheckBottom(x, y))
	{
		// �ٴ��̳� ���� ��Ҵٸ� ������ ������ �� ��ġ�� ����
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shape[rotateNumber][i][j] == 2)
				{
					int blockX = (x - 40) / 2;
					int blockY = (y - 10);

					// �� ��ġ�� 4�� ���� (���� ���� 4�� ǥ��)
					mapCopy[i + blockY][j + blockX] = 4;
				}
			}
		}
		// �� ��ġ�� �����ߴٸ� ���� ����� ����ִ� shape �迭�� �ʱ�ȭ����
		// ȭ��󿡼� ���ֵ���(����� �� �ǰԲ�) �Ѵ�.
		memset(shape, 0, sizeof(int) * 4 * 4 * 4);

		// ���� �׿��ٸ� �ٽ� ������ ���� ��ġ�� ���� ���� ��ġ�� �ǵ�����.
		info.pos.x = startPosX;
		info.pos.y = startPosY;
		canCreateBlock = true;
	}
}

// ���� ���������� mapCopy�� ��ȸ�ϸ� �� ���� �ϼ��ƴٸ� �� ���� �����ϴ� �޼���
// ���ÿ� �������� �ϼ����� ���� �Ѳ����� ���� ����
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

		if (lineClear) // ���� �� á�ٸ�
		{
			for (int j = i; j > 0; j--)
			{
				for (int k = 1; k < MAP_W - 1; k++)
				{
					mapCopy[j][k] = mapCopy[j - 1][k];
				}
			}
			++deleteLine; // ������ �� ���� ī��Ʈ ����
		}
		else
		{
			--i;
		}
	}

	this->score += deleteLine * 100; // ������ �� ���� ī��Ʈ�� ���� ���ھ� �ջ�
}

// ȸ���ؼ� ������ ���� ����� ���� ���� �հ� ��������(�浹�ϴ���) üũ�ϴ� �޼���
bool CBlocks::CheckLeft(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[(rotateNumber + 1) % 4][i][j] == 2)
			{
				int blockX = ((x - 40) / 2) - 1; // �� ĭ ���� üũ
				int blockY = (y - 10);
				if (mapCopy[blockY + i][blockX + j] == 1)
					return true;
			}
		}
	}

	return false;
}

// ���������� �������� üũ�ϴ� �޼���
bool CBlocks::CheckRight(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape[(rotateNumber + 1) % 4][i][j] == 2)
			{
				int blockX = ((x - 40) / 2) + 1; // �� ĭ ������ üũ
				int blockY = (y - 10);
				if (mapCopy[blockY + i][blockX + j] == 1)
					return true;
			}
		}
	}

	return false;
}

// ���� ������ üũ�ϴ� �޼���
bool CBlocks::SetGameOver()
{
	for (int j = 0; j < MAP_W; ++j)
	{
		if (mapCopy[0][j] == 4) // �� ���ٿ� ���� ���δٸ� (���� ���� 4�� ó���ϱ�� �߾���)
			return true; // ���� ����
	}

	return false; // ���� ���� ���� �ƴ�
}

CBlocks::CBlocks(Info info)
	: Obj(info)
{
}

CBlocks::~CBlocks()
{
}
