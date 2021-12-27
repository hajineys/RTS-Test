#include "Viper.h"
#include "DRD2DEngine.h"

Viper::Viper(float posX, float posY)
	:UnitBase(posX, posY)
{
	m_Name = "Viper";
	m_UnitType = PlayerType::ENEMY;
	//m_SightRange = 200;
	//m_AttackRange = 10;
	m_AttackPower = 8;
	m_Speed = 4.0f;
}

Viper::~Viper()
{

}

void Viper::Render(DRD2DEngine* pEngine)
{
	// 대기
	m_pAnimations[0][0] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][1] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][2] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][3] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][4] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][5] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][6] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][7] = pEngine->LoadSpriteFromSheet(4, 460, 700, 141, 92, 1);
	m_pAnimations[0][8] = pEngine->LoadSpriteFromSheet(4, 265, 700, 141, 92, 1);
	m_pAnimations[0][9] = pEngine->LoadSpriteFromSheet(4, 265, 700, 141, 92, 1);

	// 이동
	m_pAnimations[1][0] = pEngine->LoadSpriteFromSheet(4, 50, 700, 135, 90, 1);
	m_pAnimations[1][1] = pEngine->LoadSpriteFromSheet(4, 50, 700, 135, 90, 1);
	m_pAnimations[1][2] = pEngine->LoadSpriteFromSheet(4, 50, 700, 135, 90, 1);
	m_pAnimations[1][3] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);
	m_pAnimations[1][4] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);
	m_pAnimations[1][5] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);
	m_pAnimations[1][6] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);
	m_pAnimations[1][7] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);
	m_pAnimations[1][8] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);
	m_pAnimations[1][9] = pEngine->LoadSpriteFromSheet(4, 460, 700, 135, 90, 1);

	// 공격

	// 임시로 수습하는 코드
	m_pSprite = m_pAnimations[0][0];
	UnitBase::Render(pEngine);
}

void Viper::ActiveSkill()
{
	// 특정범위(유닛 기준)안에 들어온 적에게 도트 데미지를 준다
	m_ActionCount--;
}

void Viper::PassiveSkill()
{

}