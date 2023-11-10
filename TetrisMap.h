#pragma once
#include "Obj.h"

class TetrisMap :
    public Obj
{
public:
    // 맵을 그릴 배열 (0은 빈 공간, 1은 벽으로 만들 예정)
    int map[MAP_H][MAP_W];

public:
    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;

public:
    TetrisMap();
    TetrisMap(Info info);
    virtual ~TetrisMap();
};

