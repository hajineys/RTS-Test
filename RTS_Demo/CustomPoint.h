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

	void Normalize();		// 정규화
	float Length();			// 길이
};