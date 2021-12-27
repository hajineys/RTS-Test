#pragma once
#include "UnitBase.h"

class DRD2DEngine;

class Sharpshooter : public UnitBase
{
public:
	Sharpshooter(float posX, float posY);
	~Sharpshooter();

	virtual void Render(DRD2DEngine* pEngine) override;

	virtual void ActiveSkill() override;
	virtual void PassiveSkill() override;
};