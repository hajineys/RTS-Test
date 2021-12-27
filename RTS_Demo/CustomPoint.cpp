#include "CustomPoint.h"
#include <math.h>

CustomPoint::CustomPoint()
	:m_PosX(0), m_PosY(0)
{

}

CustomPoint::CustomPoint(float posX, float posY)
	: m_PosX(posX), m_PosY(posY)
{

}

CustomPoint::~CustomPoint()
{

}

CustomPoint CustomPoint::operator+(const CustomPoint& r)
{
	CustomPoint result;
	result.m_PosX = this->m_PosX + r.m_PosX;
	result.m_PosY = this->m_PosY + r.m_PosY;

	return result;
}

CustomPoint CustomPoint::operator-(const CustomPoint& r)
{
	CustomPoint result;
	result.m_PosX = this->m_PosX - r.m_PosX;
	result.m_PosY = this->m_PosY - r.m_PosY;

	return result;
}

CustomPoint CustomPoint::operator*(const float& f)
{
	CustomPoint result;
	result.m_PosX = this->m_PosX * f;
	result.m_PosY = this->m_PosY * f;

	return result;
}

void CustomPoint::Normalize()
{
	float sqrMag = sqrtf(powf(m_PosX, 2.0f) + powf(m_PosY, 2.0f));

	if (sqrMag == 0)
	{
		m_PosX = 0;
		m_PosY = 0;
	}
	else
	{
		m_PosX = m_PosX / sqrMag;
		m_PosY = m_PosY / sqrMag;
	}
}

float CustomPoint::Length()
{
	float sqrMag = sqrtf(powf(m_PosX, 2.0f) + powf(m_PosY, 2.0f));

	return sqrMag;
}