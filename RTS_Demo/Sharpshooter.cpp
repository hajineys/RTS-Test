#include "Sharpshooter.h"
#include "DRD2DEngine.h"

Sharpshooter::Sharpshooter(float posX, float posY)
	:UnitBase(posX, posY)
{
	m_Name = "Sharpshooter";
	m_UnitType = PlayerType::PLAYER;
	//m_SightRange = 200;			// 임시로 높게 잡았다(원래는 패시브 스킬을 이용하여 동료의 시야 범위를 더한다)
	//m_AttackRange = 10;			// 임시로 높게 잡았다(원래는 패시브 스킬을 이용하여 동료의 시야 범위를 더한다)
	m_AttackPower = 10;
	m_Speed = 5.0f;
}

Sharpshooter::~Sharpshooter()
{

}

void Sharpshooter::Render(DRD2DEngine* pEngine)
{
	// 대기
	m_pAnimations[0][0] = pEngine->LoadSpriteFromSheet(2, 75, 580, 100, 100, 1);
	m_pAnimations[0][1] = pEngine->LoadSpriteFromSheet(2, 75, 580, 100, 100, 1);
	m_pAnimations[0][2] = pEngine->LoadSpriteFromSheet(2, 75, 580, 100, 100, 1);
	m_pAnimations[0][3] = pEngine->LoadSpriteFromSheet(2, 75, 580, 100, 100, 1);
	m_pAnimations[0][4] = pEngine->LoadSpriteFromSheet(2, 75, 580, 100, 100, 1);
	m_pAnimations[0][5] = pEngine->LoadSpriteFromSheet(2, 65, 830, 115, 100, 1);
	m_pAnimations[0][6] = pEngine->LoadSpriteFromSheet(2, 65, 830, 115, 100, 1);
	m_pAnimations[0][7] = pEngine->LoadSpriteFromSheet(2, 65, 830, 115, 100, 1);
	m_pAnimations[0][8] = pEngine->LoadSpriteFromSheet(2, 65, 830, 115, 100, 1);
	m_pAnimations[0][9] = pEngine->LoadSpriteFromSheet(2, 65, 830, 115, 100, 1);

	// 이동
	m_pAnimations[1][0] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][1] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][2] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][3] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][4] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][5] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][6] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][7] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][8] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);
	m_pAnimations[1][9] = pEngine->LoadSpriteFromSheet(2, 1585, 335, 140, 100, 1);

	// 공격

	// 임시로 수습하는 코드
	m_pSprite = m_pAnimations[0][0];
	UnitBase::Render(pEngine);
}

void Sharpshooter::ActiveSkill()
{
	// 권총 사용 가능(데미지가 낮다)
	m_ActionCount--;
}

void Sharpshooter::PassiveSkill(/*UnitBase* punit*/)
{
	//UnitBase* unit;

	// 동료의 시야에 들어온 적을 공격할 수 있다
	//m_AttackRange += unit->m_AttackRange;
}