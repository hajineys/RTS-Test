#pragma once
#include "UnitBase.h"

class DRD2DEngine;

class Sectoid : public UnitBase
{
public:
	Sectoid(float posX, float posY);
	~Sectoid();

	virtual void Render(DRD2DEngine* pEngine) override;

	virtual void ActiveSkill() override;
	virtual void PassiveSkill() override;
};