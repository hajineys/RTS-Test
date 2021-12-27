#pragma once
#include "UnitBase.h"

class DRD2DEngine;

class Viper : public UnitBase
{
public:
	Viper(float posX, float posY);
	~Viper();

	virtual void Render(DRD2DEngine* pEngine) override;

	virtual void ActiveSkill() override;
	virtual void PassiveSkill() override;
};