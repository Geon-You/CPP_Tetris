#pragma once
#include "Obj.h"
#include "TetrisMap.h"

class CBlocks :
    public Obj
{
public:
    int shape[4][4][4]; // 블럭의 모양을 담아둘 멤버
    int rotateNumber; // 회전을 조절할 멤버
    int score; // 줄을 클리어 했을 때 스코어 점수를 담당할 멤버
    int nextShape[4][4][4]; // 다음에 나올 모양을 미리보기로 알려줄 배열

private:
    DWORD rotCooltime; // 회전 쿨타임
    bool isRot; // 회전이 가능한 상태인지 (쿨타임이 지나고 회전을 시켰는지)
    TetrisMap* map;
    int mapCopy[MAP_H][MAP_W]; // 맵의 데이터를 복사해와서 담아둘 배열
    list<int> nextShapes; // 랜덤으로 뽑힌 블럭의 모양들을 담아둘 리스트

private:
    bool canCreateBlock; // 블럭이 바닥에 쌓여야만 새로운 블럭을 생성하는데 이것을 결정할 flag
    int startPosX; // 블럭이 내려오는 초기 위치를 저장할 멤버
    int startPosY; // 블럭이 내려오는 초기 위치를 저장할 멤버

public:
    void SetMap(TetrisMap* map) { this->map = map; }

public:
    // Obj을(를) 통해 상속됨
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
