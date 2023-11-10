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

    string scoreStr; // ���ھ� ������ �޾ƿͼ� ���ڿ��� ������� ����
    char scoreBuffer[128]; // ���ھ� ���� ���ڿ��� ���� ����

public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void PrintScore();

public:
    Ingame();
    virtual ~Ingame();
};
