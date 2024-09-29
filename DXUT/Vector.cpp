#include  "Vector.h"
// ---------------------------------------------------------------------------------
#include "Position.h"
#include <cmath>
#include <stdexcept>
//#include "Error.h"
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

float Vector::Module() const
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
Vector Vector::Unitary() const
{
	float module = this->Module();
	if(module == 0)
		throw std::runtime_error("E_DIVISION_BY_ZERO");
	return *this / module;
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
	return this->Unitary() == other.Unitary();
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
		throw std::runtime_error("E_DIVISION_BY_ZERO");
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


/// <summary>
/// Computes the dot product of two vectors
/// </summary>
/// <param name="A">A The first vector</param>
/// <param name="B">B The second vector</param>
/// <returns>The dot product of vectors A and B</returns>
float Vector::DotProduct(const Vector& A, const Vector& B) {
	return A.x() * B.x() + A.y() * B.y() + A.z() * B.z();
}


/// <summary>
/// Projects vector A onto vector B
/// </summary>
/// <param name="A">The vector to be projected</param>
/// <param name="B">The vector onto which A is projected</param>
/// <returns>The projection of vector A onto vector B</returns>
Vector Vector::Project(const Vector& A, const Vector& B) {
	float mag = B.Module();
	return  B * (Vector::DotProduct(A, B) / (mag * mag));
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

