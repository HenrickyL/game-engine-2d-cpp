#include "Point.h"
// ---------------------------------------------------------------------------------
#include "cmath"
#include "Vector.h"
// ---------------------------------------------------------------------------------

Point::Point() : _x(0), _y(0), _z(0) {}
// ---------------------------------------------------------------------------------

Point::Point(float x, float y, float z): _x(x), _y(y), _z(z) {}
// ---------------------------------------------------------------------------------
Point::Point(Point* p)
{
	_x = p->_x;
	_y = p->_y;
	_z = p->_z;
}
// ---------------------------------------------------------------------------------

Point::~Point()
{
	
}
// ---------------------------------------------------------------------------------


float Point::Distance(Point* p)
{
	float difX = p->X() - this->X();
	float difY = p->Y() - this->Y();
	float difZ = p->Z() - this->Z();

	return std::sqrt(difX * difX + difY * difY + difZ * difZ);
}
// ---------------------------------------------------------------------------------
Point Point::Translate(const Point delta)
{
	_x += delta._x;
	_y += delta._y;
	_z += delta._z;
	return Point(_x, _y, _z);
}
// ---------------------------------------------------------------------------------

void Point::MoveTo(const Point position)
{
	_x = position._x;
	_y = position._y;
	_z = position._z;
}
// ---------------------------------------------------------------------------------
Point Point::operator+(const Point& other) const
{
	return Point(_x + other._x, _y + other._y, _z + other._z);
}

Point Point::operator*(const float value) const {
	return Point(_x * value, _y * value, _z * value);
}
Vector	Point::operator-(const Point& other) const
{
	return Vector(_x -other._x, _y - other._y, _z - other._z);
}