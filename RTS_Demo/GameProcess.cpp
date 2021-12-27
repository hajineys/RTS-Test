#include "GameProcess.h"
#include "DRD2DEngine.h"
#include "UnitManager.h"
#include "D2DSprite.h"
#include "DRTimer.h"

GameProcess::GameProcess(HWND hWnd, int screenWidth, int screenHeight)
	:m_hWnd(hWnd), m_ClientWidth(screenWidth), m_ClientHeight(screenHeight),
	m_Deltatime(0.0f),
	m_pD2DEngine(nullptr),
	m_pUnitManager(nullptr),
	m_pBackground(nullptr)
{

}

GameProcess::~GameProcess()
{

}

void GameProcess::Initialize()
{
	m_pD2DEngine = new DRD2DEngine;
	m_pD2DEngine->Initialize(nullptr, m_hWnd, m_ClientWidth, m_ClientHeight);

	m_pUnitManager = new UnitManager(m_hWnd, m_pD2DEngine);

	// 스프라이트 시트를 로드한다
	int BackgroundNum = m_pD2DEngine->LoadSpriteSheet("../resource/Background02.png");
	int RangerSheetNum = m_pD2DEngine->LoadSpriteSheet("../resource/239_hd2_diffuse.png");
	int ShooterSheetNum = m_pD2DEngine->LoadSpriteSheet("../resource/250_hd2_diffuse.png");
	int SectoidSheetNum = m_pD2DEngine->LoadSpriteSheet("../resource/033_hd2_diffuse.png");
	int ViperSheetNum = m_pD2DEngine->LoadSpriteSheet("../resource/025_hd2_diffuse.png");

	m_pUnitManager->CreateUnit(UnitType::RANGER, 300.0f, 300.0f);
	m_pUnitManager->CreateUnit(UnitType::SHARPSHOOTER, 300.0f, 600.0f);
	m_pUnitManager->CreateUnit(UnitType::SECTOID, 900.0f, 300.0f);
	m_pUnitManager->CreateUnit(UnitType::VIPER, 900.0f, 600.0f);

	m_pBackground = m_pD2DEngine->LoadSpriteFromSheet(BackgroundNum, 0, 0, 1920, 1080, 1);
}

void GameProcess::Update(float deltTime)
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		SendMessage(m_hWnd, WM_DESTROY, 0, 0);
	}

	m_pUnitManager->UpdateAll(deltTime);
	m_pUnitManager->UpdateAll(deltTime);
	m_pUnitManager->UpdateAll(deltTime);
}

void GameProcess::Render()
{
	m_pD2DEngine->BeginRender();

	m_pD2DEngine->DrawSprite(m_pBackground, 0, 0);
	m_pUnitManager->RenderAll();

	m_pD2DEngine->DrawText(10, 10, "F5 : 유닛 정보 표시");
	m_pD2DEngine->DrawText(10, 25, "F6 : 유닛 공격사거리 표시");

	m_pD2DEngine->EndRender();
}

void GameProcess::Finalize()
{
	m_pD2DEngine->Finalize();
	delete m_pD2DEngine;
	m_pD2DEngine = nullptr;

	delete m_pUnitManager;
	m_pUnitManager = nullptr;
}