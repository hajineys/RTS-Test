#pragma once

class CustomPoint
{
public:
	CustomPoint();
	CustomPoint(float posX, float posY);
	~CustomPoint();

	CustomPoint operator+(const CustomPoint& r);
	CustomPoint operator-(const CustomPoint& r);
	CustomPoint operator*(const float& f);

	float m_PosX;
	float m_PosY;

	void Normalize();		// ����ȭ
	float Length();			// ����
};