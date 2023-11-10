#pragma once
#include "Include.h"
#include "Screen.h"

class Obj abstract
{
protected:
	// info 정보를 저장할 객체(이름과 좌표)
	Info info;

public:
	// info 정보를 가져오는 접근자
	Info GetInfo() { return info; }

public:
	virtual void Init() abstract; // 초기화
	virtual SceneType Update() abstract; // 연산
	virtual void Render() abstract; // 그리기
	virtual void Release() abstract; // 객체 파괴 시, 메모리 해제

public:
	Obj();
	Obj(Info info);
	virtual ~Obj();
};

