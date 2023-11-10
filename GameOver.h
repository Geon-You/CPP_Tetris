#pragma once
#include "Scene.h"
#include "Include.h"

class GameOver :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual SceneType Update() override;
    virtual void Render() override;
    virtual void Release() override;

public:
    GameOver();
    virtual ~GameOver();
};

