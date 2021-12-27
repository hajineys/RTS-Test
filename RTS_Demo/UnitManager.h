#pragma once
#include <windows.h>
#include <vector>
using namespace std;

#include "UnitDefine.h"

class DRD2DEngine;
class UnitBase;

/// <summary>
/// ������ ����, ����, �����ϴ� �Ŵ��� Ŭ����
/// 
/// 2021. 04. 28 Hacgeum
/// </summary>
class UnitManager
{
public:
	UnitManager(HWND hWnd, DRD2DEngine* pEngine);
	~UnitManager();

	void UpdateAll(float deltTime);
	void RenderAll();

	void CreateUnit(UnitType type, float posX, float posY);
	void RemoveUnit();

	int GetUnitCount();

	// Move(��ġ�� �ٲ� ����)-----------------------------------
	void MoveToDestination(float x, float y);
	//---------------------------------------------------------

	// Attack(��ġ�� �ٲ� ����)---------------------------------
	UnitBase* CheckCloseEnemy();
	UnitBase* CheckEnemyIsSpotted();
	//---------------------------------------------------------

private:
	vector<UnitBase*> m_UnitPool;
	int m_UnitPoolIndex;

	// ���⿡ ������ �ȵȴٰ� �����ϴµ�.. �ϴ� �ӽ÷� ���� �ϰ� ����
	DRD2DEngine* m_pD2DEngine;

	// Input(��ġ�� �ٲ� ����)------------------------------------
public:
	void DrawSelectBox();
	void SelectUnits(int left, int top, int right, int bottom);
	void Swap(int& a, int& b);

	void UserInput();

private:
	HWND m_hWnd;

	POINT m_NowMousePos;
	POINT m_DragStartPos;

	bool m_LeftButDown;
	bool m_RightButDown;

	bool m_IsLeftDragging;

	//bool m_IsTabButDown;
	//---------------------------------------------------------
};