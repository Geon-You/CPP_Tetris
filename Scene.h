#pragma once
#include "Include.h"
#include "Define.h"
#include "Screen.h"

// Title, Ingame, GameOver ���� ���̽��� �Ǵ� �߻� Ŭ����
class Scene abstract
{
public:
	// �� ���� �� �ʱ�ȭ
	virtual void Init() abstract;
	// ������ ��� ������ ���� (���� Ű �Է� ���������)
	virtual SceneType Update() abstract;
	// ���� ������(ȭ�鿡 ������ ����� ������)
	virtual void Render() abstract;
	// �� �ı��� �޸� ����
	virtual void Release() abstract;

public:
	Scene();
	// �߻�Ŭ�����̴� ���� �Ҹ��� �������� �ۼ��ϱ�
	virtual ~Scene();
};
