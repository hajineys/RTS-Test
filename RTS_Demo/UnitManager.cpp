#include "UnitManager.h"
#include "DRD2DEngine.h"

#include "Ranger.h"
#include "Sharpshooter.h"
#include "Sectoid.h"
#include "Viper.h"

UnitManager::UnitManager(HWND hWnd, DRD2DEngine* pEngine)
	:m_UnitPoolIndex(0), m_UnitPool(0),
	m_pD2DEngine(pEngine),
	m_hWnd(hWnd),
	m_NowMousePos(),
	m_DragStartPos(),
	m_LeftButDown(false),
	m_RightButDown(false),
	m_IsLeftDragging(false)
{

}

UnitManager::~UnitManager()
{
	m_UnitPool.clear();
}

void UnitManager::UpdateAll(float deltTime)
{
	UserInput();

	// ���� �þ߰Ÿ� �ȿ� ���Դ°��� üũ�Ѵ�
	CheckCloseEnemy();

	// ���� ��Ÿ� �ȿ� ���Դ°��� üũ�Ѵ�
	CheckEnemyIsSpotted();

	for (UnitBase* i : m_UnitPool)
	{
		i->Update(deltTime);
	}

	// ���� ���ֵ��� �����Ѵ�
	RemoveUnit();
}

void UnitManager::RenderAll()
{
	for (UnitBase* i : m_UnitPool)
	{
		i->Render(m_pD2DEngine);
	}

	this->DrawSelectBox();
	m_pD2DEngine->DrawRectangle(m_NowMousePos.x - 50.0f, m_NowMousePos.y - 70.0f,
		m_NowMousePos.x + 40.0f, m_NowMousePos.y + 20.0f);

	m_pD2DEngine->DrawText(10, 100, "m_LeftButDown : %d", m_LeftButDown);
	m_pD2DEngine->DrawText(10, 120, "m_IsLeftDragging : %d", m_IsLeftDragging);

	m_pD2DEngine->DrawText(10, 170, "m_DragStartMousePos : %d %d", m_DragStartPos.x, m_DragStartPos.y);
	m_pD2DEngine->DrawText(10, 190, "m_NowMousePos : %d %d", m_NowMousePos.x, m_NowMousePos.y);

	m_pD2DEngine->DrawText(10, 300, "���� ī��Ʈ : %d", this->GetUnitCount());
}

void UnitManager::CreateUnit(UnitType type, float posX, float posY)
{
	UnitBase* newUnit = nullptr;

	switch (type)
	{
		case UnitType::RANGER:
		{
			Ranger* newRanger = new Ranger(posX, posY);
			newUnit = newRanger;
		}
		break;
		case UnitType::SHARPSHOOTER:
		{
			Sharpshooter* newShooter = new Sharpshooter(posX, posY);
			newUnit = newShooter;
		}
		break;
		case UnitType::SECTOID:
		{
			Sectoid* newSectoid = new Sectoid(posX, posY);
			newUnit = newSectoid;
		}
		break;
		case UnitType::VIPER:
		{
			Viper* newViper = new Viper(posX, posY);
			newUnit = newViper;
		}
		break;
	}

	// ���� ������ ���� ����ũ�� �ε����� �ο� �� �ش�
	static int count = 1;
	newUnit->SetIndex(count);
	count++;

	m_UnitPool.push_back(newUnit);
	m_UnitPoolIndex = m_UnitPool.size();
}

void UnitManager::RemoveUnit()
{
	std::vector<UnitBase*>::iterator iter;
	for (iter = m_UnitPool.begin(); iter != m_UnitPool.end();)
	{
		UnitBase* nowUnit = *iter;
		if (nowUnit->GetNowState() == UnitState::DEAD)
		{
			delete nowUnit;
			iter = m_UnitPool.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

int UnitManager::GetUnitCount()
{
	return m_UnitPool.size();
}

void UnitManager::MoveToDestination(float x, float y)
{
	// Unit�� ����ִ� �ڷᱸ���� ��ȸ�Ѵ�
	for (UnitBase* unit : m_UnitPool)
	{
		if (unit->GetIsSelected() == true)
		{
			unit->SetDestination(x + rand() % 30 - 7.0f, y + rand() % 30 - 30.0f);
			unit->SetNowState(UnitState::MOVE);
		}
	}
}

UnitBase* UnitManager::CheckCloseEnemy()
{
	// ��ü ������ ���鼭
	for (UnitBase* myUnit : m_UnitPool)
	{
		/// ���� ���� ����
		// ��ü ��� ������ ���鼭
		for (UnitBase* targetUnit : m_UnitPool)
		{
			if (myUnit == targetUnit) continue;

			// ��� ������ ���� ���
			if (myUnit->GetUnitType() != targetUnit->GetUnitType())
			{
				float R1 = myUnit->GetSightRange();
				float R2 = targetUnit->GetSightRange();

				float baseline = myUnit->GetPos().m_PosX - targetUnit->GetPos().m_PosX;
				float height = myUnit->GetPos().m_PosY - targetUnit->GetPos().m_PosY;
				float hypotenuse = pow(baseline, 2) + pow(height, 2);
				float interval = sqrt(hypotenuse);

				if (interval <= R1 + R2)
				{
					// �� ���� �����͸� �������ش�,
					myUnit->SetTarget(targetUnit);

					myUnit->SetNowState(UnitState::ATTACKREADY);
				}
			}
		}
	}

	return nullptr;
}

UnitBase* UnitManager::CheckEnemyIsSpotted()
{
	// ��ü ������ ���鼭
	for (UnitBase* myUnit : m_UnitPool)
	{
		/// ���� ���� ����
		// ��ü ��� ������ ���鼭
		for (UnitBase* targetUnit : m_UnitPool)
		{
			if (myUnit == targetUnit) continue;

			// ���� �̹� �������̾��ٸ� �н�
			if (myUnit->GetNowState() == UnitState::ATTACK) continue;

			// ��� ������ ���� ���
			if (myUnit->GetUnitType() != targetUnit->GetUnitType())
			{
				// ��(���� ����)�� ��ġ���Ϳ� ���� ��ġ���͸� ���� ������ ���
				CustomPoint distanceVec = myUnit->GetPos() - targetUnit->GetPos();
				float distance = abs(distanceVec.Length());

				// ���� ������ ������ ���
				if (distance <= myUnit->GetAttackRange())
				{
					/// ���� ���¸� ���������� �ٲ�
					myUnit->SetNowState(UnitState::ATTACK);
				}
			}
		}
	}

	// ��� ���Ҵµ� ��ã�� ���
	return nullptr;
}

void UnitManager::DrawSelectBox()
{
	if (m_IsLeftDragging == true)
	{
		m_pD2DEngine->DrawRectangle(m_DragStartPos.x - 7.0f, m_DragStartPos.y - 30.0f,
			m_NowMousePos.x - 7.0f, m_NowMousePos.y - 30.0f, RGB(0, 255, 0));
	}
}

void UnitManager::SelectUnits(int left, int top, int right, int bottom)
{
	// �巡�׸� �»󿡼� ���Ϸθ� ���� ���� ��찡 �ִ�
	// �� ���� left�� top�� ���� ���� ��������� �Ѵ�
	if (right < left)
	{
		Swap(left, right);
	}

	if (bottom < top)
	{
		Swap(top, bottom);
	}

	for (unsigned int i = 0; i < m_UnitPool.size(); i++)
	{
		UnitBase* unit = m_UnitPool[i];

		if (left <= unit->GetPos().m_PosX &&
			unit->GetPos().m_PosX <= right &&
			top <= unit->GetPos().m_PosY &&
			unit->GetPos().m_PosY <= bottom &&
			unit->GetUnitType() == PlayerType::PLAYER)
		{
			unit->SetIsSelected(true);
		}
		else
		{
			unit->SetIsSelected(false);
		}
	}
}

void UnitManager::Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void UnitManager::UserInput()
{
	// ���콺�� �Է��� �޴´�
	GetCursorPos(&m_NowMousePos);

	RECT rt;
	GetWindowRect(m_hWnd, &rt);
	m_NowMousePos.x -= rt.left;
	m_NowMousePos.y -= rt.top;

	// ���콺 ���� ��ư
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ���õ� ���ֵ鸸 �̵��� �� �ش�.
		MoveToDestination((LONG)m_NowMousePos.x, (LONG)m_NowMousePos.y);
	}

	/// ���콺 �Է��� �� �� ����ȭ �Ѵ�.
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ���� ����
		// ������ �ȴ����� �ִٰ�, �̹� �����ӿ� ���� ��
		if (m_RightButDown == false) {}

		m_RightButDown = true;
	}
	else
	{
		// �ȴ��� ����
		// ������ ������ �ִٰ�, �̹� �����ӿ� ������ ��
		if (m_RightButDown == true) {}

		m_RightButDown = false;
	}

	/// ���콺 �Է��� �� �� ����ȭ �Ѵ�.
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// ���� ����
		// ������ �ȴ����� �ִٰ�, �̹� �����ӿ� ���� ��
		if (m_LeftButDown == false)
		{
			m_DragStartPos = m_NowMousePos;

		}

		// ù Ŭ�� �����ǰ� ���� ���콺 �������� ��ġ�� ���� �ٸ��� �巡�� �ϰ��ִ� ���̶� �Ǵ�
		if (m_DragStartPos.x < m_NowMousePos.x || m_DragStartPos.y < m_NowMousePos.y ||
			m_NowMousePos.x < m_DragStartPos.x || m_NowMousePos.y < m_DragStartPos.y)
		{
			m_IsLeftDragging = true;
		}

		m_LeftButDown = true;
	}
	else
	{
		// �ȴ��� ����
		// ������ ������ �ִٰ�, �̹� �����ӿ� ������ ��
		if (m_LeftButDown == true && m_IsLeftDragging == false)
		{
			SelectUnits((float)m_NowMousePos.x - 50.0f, (float)m_NowMousePos.y - 70.0f,
				(float)m_NowMousePos.x + 40.0f, (float)m_NowMousePos.y + 20.0f);
		}

		if (m_IsLeftDragging == true)
		{
			SelectUnits(m_DragStartPos.x, m_DragStartPos.y,
				m_NowMousePos.x, m_NowMousePos.y);
		}

		m_LeftButDown = false;
		m_IsLeftDragging = false;
	}

	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		//m_IsTabButDown = true;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		// Unit�� ����ִ� �ڷᱸ���� ��ȸ �Ѵ�
		for (unsigned int i = 0; i < m_UnitPool.size(); i++)
		{
			UnitBase* unit = m_UnitPool[i];
			unit->SetDestination(1920 / 2, 1080 / 2);
			unit->SetNowState(UnitState::MOVE);
		}
	}

	if (GetAsyncKeyState('1') & 0x8001)
	{
		CreateUnit(UnitType::RANGER, 300.0f + rand() % 50, 300.0f + rand() % 50);
	}

	if (GetAsyncKeyState('2') & 0x8001)
	{
		CreateUnit(UnitType::SHARPSHOOTER, 300.0f + rand() % 50, 600.0f + rand() % 50);
	}

	if (GetAsyncKeyState('3') & 0x8001)
	{
		CreateUnit(UnitType::SECTOID, 900.0f + rand() % 50, 300.0f + rand() % 50);
	}

	if (GetAsyncKeyState('4') & 0x8001)
	{
		CreateUnit(UnitType::VIPER, 900.0f + rand() % 50, 600.0f + rand() % 50);
	}
}