#pragma once
#include <windows.h>
#include <vector>
using namespace std;

#include "UnitDefine.h"

class DRD2DEngine;
class UnitBase;

/// <summary>
/// 유닛의 생성, 삭제, 관리하는 매니저 클래스
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

	// Move(위치는 바뀔 예정)-----------------------------------
	void MoveToDestination(float x, float y);
	//---------------------------------------------------------

	// Attack(위치는 바뀔 예정)---------------------------------
	UnitBase* CheckCloseEnemy();
	UnitBase* CheckEnemyIsSpotted();
	//---------------------------------------------------------

private:
	vector<UnitBase*> m_UnitPool;
	int m_UnitPoolIndex;

	// 여기에 있으면 안된다고 생각하는데.. 일단 임시로 구현 하고 보자
	DRD2DEngine* m_pD2DEngine;

	// Input(위치는 바뀔 예정)------------------------------------
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