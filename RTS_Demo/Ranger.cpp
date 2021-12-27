#include "Ranger.h"
#include "DRD2DEngine.h"

Ranger::Ranger(float posX, float posY)
	:UnitBase(posX, posY)
{
	m_Name = "Ranger";
	m_UnitType = PlayerType::PLAYER;
	//m_SightRange = 150;
	//m_AttackRange = 10;
	m_AttackPower = 15;
	m_Speed = 7.0f;
}

Ranger::~Ranger()
{

}

void Ranger::Render(DRD2DEngine* pEngine)
{
	// 대기
	m_pAnimations[0][0] = pEngine->LoadSpriteFromSheet(1, 55, 140, 50, 50, 1);
	m_pAnimations[0][1] = pEngine->LoadSpriteFromSheet(1, 55, 140, 50, 50, 1);
	m_pAnimations[0][2] = pEngine->LoadSpriteFromSheet(1, 55, 140, 50, 50, 1);
	m_pAnimations[0][3] = pEngine->LoadSpriteFromSheet(1, 55, 140, 50, 50, 1);
	m_pAnimations[0][4] = pEngine->LoadSpriteFromSheet(1, 55, 140, 50, 50, 1);
	m_pAnimations[0][5] = pEngine->LoadSpriteFromSheet(1, 55, 255, 50, 50, 1);
	m_pAnimations[0][6] = pEngine->LoadSpriteFromSheet(1, 55, 255, 50, 50, 1);
	m_pAnimations[0][7] = pEngine->LoadSpriteFromSheet(1, 55, 255, 50, 50, 1);
	m_pAnimations[0][8] = pEngine->LoadSpriteFromSheet(1, 55, 255, 50, 50, 1);
	m_pAnimations[0][9] = pEngine->LoadSpriteFromSheet(1, 55, 255, 50, 50, 1);

	// 이동
	m_pAnimations[1][0] = pEngine->LoadSpriteFromSheet(1, 680, 930, 50, 50, 1);
	m_pAnimations[1][1] = pEngine->LoadSpriteFromSheet(1, 680, 930, 50, 50, 1);
	m_pAnimations[1][2] = pEngine->LoadSpriteFromSheet(1, 1305, 1265, 50, 50, 1);
	m_pAnimations[1][3] = pEngine->LoadSpriteFromSheet(1, 1305, 1265, 50, 50, 1);
	m_pAnimations[1][4] = pEngine->LoadSpriteFromSheet(1, 525, 815, 50, 50, 1);
	m_pAnimations[1][5] = pEngine->LoadSpriteFromSheet(1, 525, 815, 50, 50, 1);
	m_pAnimations[1][6] = pEngine->LoadSpriteFromSheet(1, 1305, 1265, 50, 50, 1);
	m_pAnimations[1][7] = pEngine->LoadSpriteFromSheet(1, 1305, 1265, 50, 50, 1);
	m_pAnimations[1][8] = pEngine->LoadSpriteFromSheet(1, 525, 815, 50, 50, 1);
	m_pAnimations[1][9] = pEngine->LoadSpriteFromSheet(1, 525, 815, 50, 50, 1);

	// 공격
	m_pAnimations[2][0] = pEngine->LoadSpriteFromSheet(1, 370, 475, 50, 50, 1);
	m_pAnimations[2][1] = pEngine->LoadSpriteFromSheet(1, 370, 475, 50, 50, 1);
	m_pAnimations[2][2] = pEngine->LoadSpriteFromSheet(1, 530, 475, 50, 50, 1);
	m_pAnimations[2][3] = pEngine->LoadSpriteFromSheet(1, 530, 475, 50, 50, 1);
	m_pAnimations[2][4] = pEngine->LoadSpriteFromSheet(1, 370, 475, 50, 50, 1);
	m_pAnimations[2][5] = pEngine->LoadSpriteFromSheet(1, 370, 475, 50, 50, 1);
	m_pAnimations[2][6] = pEngine->LoadSpriteFromSheet(1, 530, 475, 50, 50, 1);
	m_pAnimations[2][7] = pEngine->LoadSpriteFromSheet(1, 530, 475, 50, 50, 1);
	m_pAnimations[2][8] = pEngine->LoadSpriteFromSheet(1, 370, 475, 50, 50, 1);
	m_pAnimations[2][9] = pEngine->LoadSpriteFromSheet(1, 370, 475, 50, 50, 1);

	// 임시로 수습하는 코드
	m_pSprite = m_pAnimations[0][0];
	UnitBase::Render(pEngine);
}

void Ranger::ActiveSkill()
{
	// 적이 가까이 있을때 공격력이 증가한다
	m_ActionCount--;
}

void Ranger::PassiveSkill()
{

}