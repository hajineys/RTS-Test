#include "UnitBase.h"
#include "DRD2DEngine.h"

bool UnitBase::m_UnitInfoFlag = false;
bool UnitBase::m_UnitSightRangeFlag = false;
bool UnitBase::m_UnitAttackRangeFlag = false;

UnitBase::UnitBase(float posX, float posY)
	:m_Index(0),
	m_Name("Unit"),
	m_UnitType(PlayerType::NONE),

	m_NowHP(30),
	m_HPMax(30),
	m_ActionCount(2),
	m_SightRange(250),
	m_AttackRange(150),
	m_AttackPower(20),
	m_Armor(10),
	m_Will(35),

	m_Position(posX, posY),
	m_Speed(3.0f),
	m_Destination(posX, posY),

	m_pTarget(nullptr),
	m_IsSelected(false),
	m_IsCloseEmemy(false),
	m_PrevState(UnitState::STANDBY),
	m_NowState(UnitState::STANDBY),

	m_pSprite(nullptr),
	m_pAnimations(),
	m_NowSpriteIndex(0),

	m_DeltaTime(0.0f)
{

}

UnitBase::~UnitBase()
{

}

void UnitBase::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;

	// 0~9까지 스프라이트 인덱스를 정해준다
	if (rand() % 2 == 0)
	{
		m_NowSpriteIndex++;

		if (9 < m_NowSpriteIndex)
		{
			m_NowSpriteIndex = 0;
		}
	}

	// Finite State Machine
	switch (m_NowState)
	{
		case UnitState::STANDBY:
		{
			//m_Position.m_PosX += (rand() % 2 - rand() % 2);
			//m_Position.m_PosY += (rand() % 2 - rand() % 2);
		}
		break;
		case UnitState::MOVE:
		{
			Move();
		}
		break;
		case UnitState::ATTACKREADY:
		{
			Move();
		}
		break;
		case UnitState::ATTACK:
		{
			// 공격중 상태인데, 타겟이 있다면 실제로 공격
			if (m_pTarget != nullptr)
			{
				Attack(m_pTarget);
			}
		}
		break;
		case UnitState::DEAD:
		{
			// 뒤짐
		}
		break;
	}

	// 도착했는지를 체크한다
	CheckIsArrived();

	// 죽음을 체크한다
	CheckDead();

	// 적의 죽음을 체크한다
	CheckEnemyDead();
}

void UnitBase::Render(DRD2DEngine* pEngine)
{

	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		m_UnitInfoFlag ^= true;
	}

	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		m_UnitSightRangeFlag ^= true;
	}

	if (GetAsyncKeyState(VK_F7) & 0x0001)
	{
		m_UnitAttackRangeFlag ^= true;
	}

	DrawMoveLine(pEngine);

	ShowUnitInfo(pEngine);
	ShowSightRange(pEngine);
	ShowAttackRange(pEngine);

	int animationIndex = 0;

	if (m_NowState == UnitState::MOVE)
	{
		animationIndex = 1;
	}
	else if (m_NowState == UnitState::ATTACKREADY)
	{
		animationIndex = 0;
	}
	else if (m_NowState == UnitState::ATTACK)
	{
		animationIndex = 1;
	}
	else if (m_NowState == UnitState::DEAD)
	{
		//animationIndex = 3;
	}
	else
	{
		animationIndex = 0;
	}

	pEngine->DrawSprite(m_pAnimations[animationIndex][m_NowSpriteIndex],
		m_Position.m_PosX - m_pSprite->Width / 2, m_Position.m_PosY - m_pSprite->Height / 2);
	DrawHP(pEngine, (float)m_NowHP / (float)m_HPMax);

	// 선택된 상태인가?를 그려준다
	DrawSelected(pEngine);
}

void UnitBase::Move()
{
	// 현재 포지션에 이동벡터를 구한다
	CustomPoint moveVec = m_Destination - m_Position;

	// 노말라이즈를 한다.
	moveVec.Normalize();

	// 현재 위치에서 목적지로 이동한다
	m_Position = m_Position + (moveVec * m_Speed);
}

void UnitBase::Attack(UnitBase* target)
{
	int targetHP = target->GetNowHP();

	// 타겟의 HP에서 내 공격력을 뺀다(타겟의 잔여 HP)
	// 단, HP는 0보다 아래로 내려가면 안된다
	int remainHP = max(0, targetHP - m_AttackPower);

	// 타겟의 HP를 설정해준다
	target->SetNowHP(targetHP - m_AttackPower);

	// 적이 죽었다면 타겟을 리셋해준다
	if (target->GetNowState() == UnitState::DEAD)
	{
		m_pTarget = nullptr;

		// 이전 상태로 복귀한다
		m_NowState = m_PrevState;
	}
}

void UnitBase::CheckCloseEmeny()
{

}

void UnitBase::CheckDead()
{
	if (m_NowHP <= 0)
	{
		m_NowHP = 0;
		SetNowState(UnitState::DEAD);
	}
}

void UnitBase::CheckEnemyDead()
{
	if (m_pTarget != nullptr)
	{
		if (m_pTarget->m_NowState == UnitState::DEAD)
		{
			SetNowState(UnitState::STANDBY);
		}
	}
}

void UnitBase::CheckIsArrived()
{
	// 현재 위치와 목적지의 위치의 차를 계산한다
	CustomPoint moveVec = m_Destination - m_Position;

	if (m_NowState == UnitState::MOVE && abs(moveVec.Length() < 10.0f))
	{
		this->SetNowState(UnitState::STANDBY);
	}
}

void UnitBase::SetPos(float x, float y)
{
	m_Position.m_PosX = x;
	m_Position.m_PosY = y;
}

void UnitBase::SetDestination(float x, float y)
{
	m_Destination.m_PosX = x;
	m_Destination.m_PosY = y;
}

void UnitBase::DrawSelected(DRD2DEngine* pEngine)
{
	// 선택 된 상태인가?를 그려준다
	if (m_IsSelected == true)
	{
		if (m_UnitType == PlayerType::PLAYER)
		{
			pEngine->SetBrushColor(DRCOLOR_BLUE);
		}
		else if (m_UnitType == PlayerType::ENEMY)
		{
			pEngine->SetBrushColor(DRCOLOR_RED);
		}
		else
		{ 
			pEngine->SetBrushColor(DRCOLOR_WHITE); 
		}

		pEngine->DrawRectangle(m_Position.m_PosX - m_pSprite->Width / 2, m_Position.m_PosY - m_pSprite->Height / 2,
			m_Position.m_PosX + m_pSprite->Width / 2, m_Position.m_PosY + m_pSprite->Height / 2, DRCOLOR_WHITE);
	}
}

void UnitBase::DrawMoveLine(DRD2DEngine* pEngine)
{
	pEngine->DrawLine(m_Position.m_PosX, m_Position.m_PosY, m_Destination.m_PosX, m_Destination.m_PosY);
}

void UnitBase::DrawHP(DRD2DEngine* pEngine, float value)
{
	float widthHP = m_pSprite->Width / 2 * value;

	pEngine->DrawRectangle(m_Position.m_PosX - m_pSprite->Width / 2, m_Position.m_PosY - 40.0f,
		m_Position.m_PosX + widthHP, m_Position.m_PosY - 38.0f, RGB(180, 100, 0));

	pEngine->DrawRectangle(m_Position.m_PosX - m_pSprite->Width / 2, m_Position.m_PosY - 39.0f,
		m_Position.m_PosX + widthHP, m_Position.m_PosY - 37.0f, RGB(180, 100, 0));

	pEngine->DrawRectangle(m_Position.m_PosX - m_pSprite->Width / 2, m_Position.m_PosY - 38.0f,
		m_Position.m_PosX + widthHP, m_Position.m_PosY - 36.0f, RGB(180, 100, 0));
}

void UnitBase::ShowSightRange(DRD2DEngine* pEngine)
{
	if (m_UnitSightRangeFlag == true)
	{
		pEngine->DrawEllipse(m_Position.m_PosX, m_Position.m_PosY, m_SightRange);
	}
}

void UnitBase::ShowAttackRange(DRD2DEngine* pEngine)
{
	if (m_UnitAttackRangeFlag == true)
	{
		if (m_UnitType == PlayerType::PLAYER)
		{
			pEngine->SetBrushColor(DRCOLOR_BLUE);
		}
		else if (m_UnitType == PlayerType::ENEMY)
		{
			pEngine->SetBrushColor(DRCOLOR_RED);
		}

		pEngine->DrawEllipse(m_Position.m_PosX, m_Position.m_PosY, m_AttackRange);
	}
}

void UnitBase::ShowUnitInfo(DRD2DEngine* pEngine)
{
	if (m_UnitInfoFlag == true)
	{
		pEngine->SetBrushColor(DRCOLOR_WHITE);
		pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 115.0f, m_Name.c_str());
		pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 100.0f, "Index : %d", m_Index);
		pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 85.0f, "HP : %d", m_NowHP);
		pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 70.0f, "Power : %d", m_AttackPower);

		switch (m_NowState)
		{
			case UnitState::STANDBY:
			{
				pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 55.0f, "대기중");
			}
			break;
			case UnitState::MOVE:
			{
				pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 55.0f, "이동중");
			}
			break;
			case UnitState::ATTACKREADY:
			{
				pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 55.0f, "공격가능");
			}
			break;
			case UnitState::ATTACK:
			{
				pEngine->DrawText(m_Position.m_PosX - 50.0f, m_Position.m_PosY - 55.0f, "공격중");
			}
			break;
		}
	}
}

void UnitBase::SetNowState(UnitState state)
{
	// 이전 상태를 보관한다.
	m_PrevState = m_NowState;
	m_NowState = state;
}