#pragma once
#include <string>
#include "UnitDefine.h"
#include "CustomPoint.h"

class DRD2DEngine;
class DRSprite;

/// <summary>
/// ��� ���ֵ��� �⺻ ���� Ŭ����
/// 
/// 2021. 04. 28 Hacgeum
/// </summary>
class UnitBase
{
public:
	UnitBase(float posX, float posY);
	~UnitBase();

	void Update(float deltaTime);
	virtual void Render(DRD2DEngine* pEngine);
	virtual void ActiveSkill() abstract;
	virtual void PassiveSkill() abstract;
	void Move();
	void Attack(UnitBase* target);
	void CheckCloseEmeny();
	void CheckDead();
	void CheckEnemyDead();

	// �̵� ����(��ġ�� �ٲ��� �� �� ����)
	void CheckIsArrived();
	void SetPos(float x, float y);
	void SetDestination(float x, float y);

	// Status Draw
	void DrawSelected(DRD2DEngine* pEngine);
	void DrawMoveLine(DRD2DEngine* pEngine);
	void DrawHP(DRD2DEngine* pEngine, float value);

	// Debug
	void ShowSightRange(DRD2DEngine* pEngine);
	void ShowAttackRange(DRD2DEngine* pEngine);
	void ShowUnitInfo(DRD2DEngine* pEngine);

	/// Getter / Setter
public:
	int GetIndex() const { return m_Index; }
	void SetIndex(int num) { m_Index = num; }

	std::string GetName() const { return m_Name; }

	PlayerType GetUnitType() const { return m_UnitType; }
	void SetUnitType(PlayerType type) { m_UnitType = type; }

	int GetNowHP() const { return m_NowHP; }
	void SetNowHP(int hp) { m_NowHP = hp; }

	float GetSightRange() const { return m_SightRange; }

	float GetAttackRange() const { return m_AttackRange; }

	CustomPoint GetPos() const { return m_Position; }

	void SetTarget(UnitBase* target) { m_pTarget = target; }

	bool GetIsSelected() const { return m_IsSelected; }
	void SetIsSelected(bool val) { m_IsSelected = val; }

	bool GetIsCloseEmemy() const { return m_IsCloseEmemy; }

	UnitState GetNowState() const { return m_NowState; }
	void SetNowState(UnitState state);

protected:
	// ���� ����
	int m_Index;				// ����ũ�� �ε���
	std::string m_Name;			// �̸�
	PlayerType m_UnitType;		// �÷��̾��ΰ�?

	// �⺻ ���� ����
	int m_NowHP;				// ���� ü��
	int m_HPMax;				// ü��
	int m_ActionCount;			// �ൿ ���� Ƚ��
	float m_SightRange;			// �þ� ��Ÿ�
	float m_AttackRange;		// ���� ��Ÿ�
	int m_AttackPower;			// ���ݷ�
	int m_Armor;				// �尩(�Ƹ�)
	int m_Will;					// ����

	// �̵� ���� ����
	CustomPoint m_Position;		// ��ġ
	float m_Speed;				// �̵��ӵ�
	CustomPoint m_Destination;	// ������

	// ���� ����
	UnitBase* m_pTarget;		// ������ �� ���

	// 
	bool m_IsSelected;
	bool m_IsCloseEmemy;

	// FSM
	UnitState m_PrevState;
	UnitState m_NowState;

	// Draw
	DRSprite* m_pSprite;
	DRSprite* m_pAnimations[3][10];
	int m_NowSpriteIndex;

private:
	static bool m_UnitInfoFlag;
	static bool m_UnitSightRangeFlag;
	static bool m_UnitAttackRangeFlag;

private:
	float m_DeltaTime;
};