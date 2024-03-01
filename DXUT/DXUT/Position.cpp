#include "Position.h"
// ---------------------------------------------------------------------------------
#include "cmath"
#include "Vector.h"
#include <functional>
// ---------------------------------------------------------------------------------

Position Position::Zero = new Position(0, 0, 0);
// ---------------------------------------------------------------------------------

Position::Position() : _x(0), _y(0), _z(0) {}
// ---------------------------------------------------------------------------------

Position::Position(float x, float y, float z): _x(x), _y(y), _z(z) {}
// ---------------------------------------------------------------------------------
Position::Position(Position* p)
{
	_x = p->_x;
	_y = p->_y;
	_z = p->_z;
}
// ---------------------------------------------------------------------------------

Position::~Position()
{}
// ---------------------------------------------------------------------------------


float Position::Distance(const Position& p) const
{
	float difX = p.x() - this->x();
	float difY = p.y() - this->y();
	float difZ = p.z() - this->z();

	return std::sqrt(difX * difX + difY * difY + difZ * difZ);
}
// ---------------------------------------------------------------------------------
void Position::Translate(const Vector& delta)
{
	_x += delta.x();
	_y += delta.y();
	_z += delta.z();
}
// ---------------------------------------------------------------------------------

void Position::MoveTo(const Position& position)
{
	_x = position._x;
	_y = position._y;
	_z = position._z;
}
// ---------------------------------------------------------------------------------
Position Position::operator+(const Position& other) const
{
	return Position(_x + other._x, _y + other._y, _z + other._z);
}

Position Position::operator*(const float value) const {
	return Position(_x * value, _y * value, _z * value);
}

Position	Position::operator/(const float value) const {
	return Position(_x / value, _y / value, _z / value);
}

Vector	Position::operator-(const Position& other) const
{
	return Vector(_x -other._x, _y - other._y, _z - other._z);
}


std::size_t Position::customHash() const {
	std::size_t xHash = std::hash<int>{}(x());
	std::size_t yHash = std::hash<int>{}(y());
	return xHash ^ (yHash << 1);
}

bool Position::operator==(const Hasheable& outra) const {
	if (const Position* p = dynamic_cast<const Position*>(&outra)) {
		return x() == p->x() && y() == p->y();
	}
	return false;
}

