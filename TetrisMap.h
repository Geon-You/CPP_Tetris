#pragma once
#include "Obj.h"

class TetrisMap :
    public Obj
{
public:
    // ���� �׸� �迭 (0�� �� ����, 1�� ������ ���� ����)
    int map[MAP_H][MAP_W];

public:
    // Obj��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;

public:
    TetrisMap();
    TetrisMap(Info info);
    virtual ~TetrisMap();
};

