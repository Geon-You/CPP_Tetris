#pragma once
#include "Obj.h"
#include "TetrisMap.h"

class CBlocks :
    public Obj
{
public:
    int shape[4][4][4]; // ���� ����� ��Ƶ� ���
    int rotateNumber; // ȸ���� ������ ���
    int score; // ���� Ŭ���� ���� �� ���ھ� ������ ����� ���
    int nextShape[4][4][4]; // ������ ���� ����� �̸������ �˷��� �迭

private:
    DWORD rotCooltime; // ȸ�� ��Ÿ��
    bool isRot; // ȸ���� ������ �������� (��Ÿ���� ������ ȸ���� ���״���)
    TetrisMap* map;
    int mapCopy[MAP_H][MAP_W]; // ���� �����͸� �����ؿͼ� ��Ƶ� �迭
    list<int> nextShapes; // �������� ���� ���� ������ ��Ƶ� ����Ʈ

private:
    bool canCreateBlock; // ���� �ٴڿ� �׿��߸� ���ο� ���� �����ϴµ� �̰��� ������ flag
    int startPosX; // ���� �������� �ʱ� ��ġ�� ������ ���
    int startPosY; // ���� �������� �ʱ� ��ġ�� ������ ���

public:
    void SetMap(TetrisMap* map) { this->map = map; }

public:
    // Obj��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;
    void rotate();
    bool CheckCollision(int x, int y);
    bool CheckBottom(int x, int y);
    void CreateBlock();
    void BlockTouchBottom(int x, int y);
    void DeleteLine();
    bool SetGameOver();
    bool CheckLeft(int x, int y);
    bool CheckRight(int x, int y);

public:
    CBlocks(Info info);
    virtual ~CBlocks();
};
