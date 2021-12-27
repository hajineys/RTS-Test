#pragma once
#include "UnitBase.h"

class DRD2DEngine;

class Ranger :public UnitBase
{
public:
	Ranger(float posX, float posY);
	~Ranger();

	virtual void Render(DRD2DEngine* pEngine) override;

	virtual void ActiveSkill() override;
	virtual void PassiveSkill() override;
};