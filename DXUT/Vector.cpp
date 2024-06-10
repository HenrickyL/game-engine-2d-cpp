#include  "Vector.h"
// ---------------------------------------------------------------------------------
#include "Position.h"
#include <cmath>
#include "Error.h"
// ---------------------------------------------------------------------------------
Vector Vector::Forward = Vector(0,0,1);
Vector Vector::Backward = Vector(0,0,-1);
Vector Vector::Up = Vector(0,1,0);
Vector Vector::Down = Vector(0,-1,0);
Vector Vector::Left = Vector(-1, 0, 0);
/**
 * \brief (1,0,0)
 */
Vector Vector::Right = Vector(1, 0, 0);
Vector Vector::Zero = Vector(0,0,0);
Vector Vector::One = Vector(1, 1, 1);

// ---------------------------------------------------------------------------------
Vector::Vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

// ---------------------------------------------------------------------------------

float Vector::Magnitude() const
{
	float x = this->_x;
	float y = this->_y;
	float z = this->_z;
	return std::sqrt(x*x + y*y + z*z);
}

/**
 * \brief Retorna o Vetor uniário
 * \return Vector
 */
Vector Vector::Unit() const
{
	return *this / this->Magnitude();
}

Vector Vector::Inverte() const {
	return Vector(-x(), -y(), -z());
}



// ---------------------------------------------------------------------------------
/**
 * Verifica se tem Direções iguais, independente do módulo 
 * \param Vector other 
 * \return bool
 */
bool	Vector::operator<=>(const Vector& other) const
{
	return this->Unit() == other.Unit();
}
// ---------------------------------------------------------------------------------

Vector	Vector::operator+(const Vector& other) const
{
	return Vector(_x + other._x, _y + other._y, _z + other._z);
}
Vector	Vector::operator*(const float value) const
{
	return Vector(_x * value, _y * value, _z * value);
}

Vector	Vector::operator*(const Vector& other) const
{
	return Vector(_x * other.x(), _y * other.y(), _z * other.z());
}


Vector	Vector::operator/(const float value) const
{
	if (value == 0)
		throw Error(E_DIVISION_BY_ZERO);
	return Vector(_x / value, _y / value, _z / value);
}
Vector	Vector::operator-(const Vector& other) const
{
	return Vector(_x - other._x, _y - other._y, _z - other._z);
}
bool	Vector::operator==(const Vector& other) const
{
	return _x == other._x && _y == other._y && _z == other._z;
}

bool	Vector::operator!=(const Vector& other) const
{
	return ! (*this == other);
}



Vector Vector::CrossProduct(const Vector& A, const Vector& B) {
	return Vector(
		A.y() * B.z() - A.z() * B.y(),
		A.z() * B.x() - A.x() * B.z(),
		A.x() * B.y() - A.y() * B.x()
	);
}


Vector Vector::CrossProduct(const Vector& other) const {
	return Vector::CrossProduct(*this, other);
}

