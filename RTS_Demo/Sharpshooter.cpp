#include "Sharpshooter.h"
#include "DRD2DEngine.h"

Sharpshooter::Sharpshooter(float posX, float posY)
	:UnitBase(posX, posY)
{
	m_Name = "Sharpshooter";
	m_UnitType = PlayerType::PLAYER;
	//m_SightRange = 200;			// �ӽ÷� ���� ��Ҵ�(������ �нú� ��ų�� �̿��Ͽ� ������ �þ� ������ ���Ѵ�)
	//m_AttackRange = 10;			// �ӽ÷� ���� ��Ҵ�(������ �нú� ��ų�� �̿��Ͽ� ������ �þ� ������ ���Ѵ�)
	m_AttackPower = 10;
	m_Speed = 5.0f;
}

Sharpshooter::~Sharpshooter()
{

}

void Sharpshooter::Render(DRD2DEngine* pEngine)
{
	// ���
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

	// �̵�
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

	// ����

	// �ӽ÷� �����ϴ� �ڵ�
	m_pSprite = m_pAnimations[0][0];
	UnitBase::Render(pEngine);
}

void Sharpshooter::ActiveSkill()
{
	// ���� ��� ����(�������� ����)
	m_ActionCount--;
}

void Sharpshooter::PassiveSkill(/*UnitBase* punit*/)
{
	//UnitBase* unit;

	// ������ �þ߿� ���� ���� ������ �� �ִ�
	//m_AttackRange += unit->m_AttackRange;
}