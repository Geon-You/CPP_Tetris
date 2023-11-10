#pragma once
#include "Scene.h"
#include "Include.h"
#include "TetrisMap.h"
#include "CBlocks.h"

class Ingame :
    public Scene
{
private:
    Obj* map;
    Obj* block;

    string scoreStr; // 스코어 점수를 받아와서 문자열로 출력해줄 변수
    char scoreBuffer[128]; // 스코어 점수 문자열을 담을 버퍼

public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void PrintScore();

public:
    Ingame();
    virtual ~Ingame();
};
