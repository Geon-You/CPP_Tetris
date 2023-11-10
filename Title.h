#pragma once
#include "Scene.h"
#include "Include.h"

class Title :
    public Scene
{
public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;

public:
    Title();
    virtual ~Title();
};

