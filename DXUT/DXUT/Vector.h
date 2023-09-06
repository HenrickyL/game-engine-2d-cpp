#ifndef DXUT_VECTOR_H
#define DXUT_VECTOR_H
// ---------------------------------------------------------------------------------
#include "Error.h"
#include "Point.h"
// ---------------------------------------------------------------------------------
class Vector : public Point
{
public:
	static Vector Forward;
	static Vector Backward;
	static Vector Up;
	static Vector Down;
	static Vector Left;
	static Vector Right;
	static Vector Zero;


	Vector(float x, float y, float z);

	float Magnitude() const;
	Vector Unit() const;


	Vector	operator+(const Vector& other) const;
	Vector	operator*(const float value) const;
	Vector	operator/(const float value) const;
	Vector	operator-(const Vector& other) const;
	bool	operator==(const Vector& other) const;
	bool	operator<=>(const Vector& other) const; // equal direction

};





#endif