#pragma once
#include <string>
#include "UnitDefine.h"
#include "CustomPoint.h"

class DRD2DEngine;
class DRSprite;

/// <summary>
/// 모든 유닛들의 기본 정보 클래스
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

	// 이동 관련(위치가 바뀌어야 할 것 같다)
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
	// 유닛 정보
	int m_Index;				// 유니크한 인덱스
	std::string m_Name;			// 이름
	PlayerType m_UnitType;		// 플레이어인가?

	// 기본 스탯 정보
	int m_NowHP;				// 현재 체력
	int m_HPMax;				// 체력
	int m_ActionCount;			// 행동 가능 횟수
	float m_SightRange;			// 시야 사거리
	float m_AttackRange;		// 공격 사거리
	int m_AttackPower;			// 공격력
	int m_Armor;				// 장갑(아머)
	int m_Will;					// 의지

	// 이동 관련 정보
	CustomPoint m_Position;		// 위치
	float m_Speed;				// 이동속도
	CustomPoint m_Destination;	// 목적지

	// 공격 관련
	UnitBase* m_pTarget;		// 공격을 할 대상

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