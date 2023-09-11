#ifndef DXUT_VECTOR_H
#define DXUT_VECTOR_H
// ---------------------------------------------------------------------------------
#include "Position.h"
// ---------------------------------------------------------------------------------
class Vector : public Position
{
public:
	static Vector Forward;
	static Vector Backward;
	static Vector Up;
	static Vector Down;
	static Vector Left;
	static Vector Right;
	static Vector Zero;


	Vector(float x, float y, float z=0);

	float Magnitude() const;
	Vector Unit() const;


	Vector	operator+(const Vector& other) const;
	Vector	operator*(const float value) const;
	Vector	operator/(const float value) const;
	Vector	operator-(const Vector& other) const;
	bool	operator==(const Vector& other) const;
	bool	operator!=(const Vector& other) const;
	bool	operator<=>(const Vector& other) const; // equal direction

};

#endif