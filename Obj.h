#pragma once
#include "Include.h"
#include "Screen.h"

class Obj abstract
{
protected:
	// info ������ ������ ��ü(�̸��� ��ǥ)
	Info info;

public:
	// info ������ �������� ������
	Info GetInfo() { return info; }

public:
	virtual void Init() abstract; // �ʱ�ȭ
	virtual SceneType Update() abstract; // ����
	virtual void Render() abstract; // �׸���
	virtual void Release() abstract; // ��ü �ı� ��, �޸� ����

public:
	Obj();
	Obj(Info info);
	virtual ~Obj();
};

