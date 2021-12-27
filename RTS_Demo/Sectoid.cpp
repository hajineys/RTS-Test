#include "Sectoid.h"
#include "DRD2DEngine.h"

Sectoid::Sectoid(float posX, float posY)
	:UnitBase(posX, posY)
{
	m_Name = "Sectoid";
	m_UnitType = PlayerType::ENEMY;
	//m_SightRange = 150;
	//m_AttackRange = 10;
	m_AttackPower = 8;
	m_Speed = 5.0f;
}

Sectoid::~Sectoid()
{

}

void Sectoid::Render(DRD2DEngine* pEngine)
{
	// ���
	m_pAnimations[0][0] = pEngine->LoadSpriteFromSheet(3, 175, 260, 44, 68, 1);
	m_pAnimations[0][1] = pEngine->LoadSpriteFromSheet(3, 175, 260, 44, 68, 1);
	m_pAnimations[0][2] = pEngine->LoadSpriteFromSheet(3, 175, 260, 44, 68, 1);
	m_pAnimations[0][3] = pEngine->LoadSpriteFromSheet(3, 175, 260, 44, 68, 1);
	m_pAnimations[0][4] = pEngine->LoadSpriteFromSheet(3, 175, 260, 44, 68, 1);
	m_pAnimations[0][5] = pEngine->LoadSpriteFromSheet(3, 45, 260, 44, 68, 1);
	m_pAnimations[0][6] = pEngine->LoadSpriteFromSheet(3, 45, 260, 44, 68, 1);
	m_pAnimations[0][7] = pEngine->LoadSpriteFromSheet(3, 45, 260, 44, 68, 1);
	m_pAnimations[0][8] = pEngine->LoadSpriteFromSheet(3, 45, 260, 44, 68, 1);
	m_pAnimations[0][9] = pEngine->LoadSpriteFromSheet(3, 45, 260, 44, 68, 1);
	
	// �̵�
	m_pAnimations[1][0] = pEngine->LoadSpriteFromSheet(3, 1485, 1665, 44, 68, 1);
	m_pAnimations[1][1] = pEngine->LoadSpriteFromSheet(3, 1485, 1665, 44, 68, 1);
	m_pAnimations[1][2] = pEngine->LoadSpriteFromSheet(3, 1485, 1665, 44, 68, 1);
	m_pAnimations[1][3] = pEngine->LoadSpriteFromSheet(3, 1615, 1780, 44, 68, 1);
	m_pAnimations[1][4] = pEngine->LoadSpriteFromSheet(3, 1615, 1780, 44, 68, 1);
	m_pAnimations[1][5] = pEngine->LoadSpriteFromSheet(3, 1615, 1780, 44, 68, 1);
	m_pAnimations[1][6] = pEngine->LoadSpriteFromSheet(3, 1745, 1895, 44, 68, 1);
	m_pAnimations[1][7] = pEngine->LoadSpriteFromSheet(3, 1745, 1895, 44, 68, 1);
	m_pAnimations[1][8] = pEngine->LoadSpriteFromSheet(3, 1745, 1895, 44, 68, 1);
	m_pAnimations[1][9] = pEngine->LoadSpriteFromSheet(3, 1745, 1895, 44, 68, 1);

	// ����

	// �ӽ÷� �����ϴ� �ڵ�
	m_pSprite = m_pAnimations[0][0];
	UnitBase::Render(pEngine);
}

void Sectoid::ActiveSkill()
{
	// ������ ���� ���� ������ �� �ִ�
	m_ActionCount--;
}

void Sectoid::PassiveSkill()
{

}