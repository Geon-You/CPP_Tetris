#pragma once
#include "Include.h"
#include "Define.h"
#include "Screen.h"

// Title, Ingame, GameOver 씬의 베이스가 되는 추상 클래스
class Scene abstract
{
public:
	// 씬 생성 시 초기화
	virtual void Init() abstract;
	// 씬에서 계속 수행할 동작 (유저 키 입력 감지라던가)
	virtual SceneType Update() abstract;
	// 씬을 렌더링(화면에 무엇을 출력할 것인지)
	virtual void Render() abstract;
	// 씬 파괴시 메모리 해제
	virtual void Release() abstract;

public:
	Scene();
	// 추상클래스이니 가상 소멸자 잊지말고 작성하기
	virtual ~Scene();
};
