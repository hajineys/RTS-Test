#pragma once
#include <windows.h>

class DRD2DEngine;
class UnitManager;
class DRSprite;

class GameProcess
{
public:
	GameProcess(HWND hWnd, int screenWidth, int screenHeight);
	~GameProcess();

	void Initialize();
	void Update(float deltTime);
	void Render();
	void Finalize();

private:
	HWND m_hWnd;

	int m_ClientWidth;
	int m_ClientHeight;
	float m_Deltatime;

	DRD2DEngine* m_pD2DEngine;
	UnitManager* m_pUnitManager;

	// 임시변수
	DRSprite* m_pBackground;
};