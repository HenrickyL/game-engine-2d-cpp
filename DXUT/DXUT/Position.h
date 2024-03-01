#ifndef DXUT_POSITION_H
#define DXUT_POSITION_H
// --------------------------------------------
#include "Hasheable.h"
// --------------------------------------------
class Vector;
// --------------------------------------------

class Position : public Hasheable
{
protected:
	float _x=0, _y=0,_z=0;
public:
	Position();
	Position(float x, float y, float z=0);
	Position(Position* p);
	~Position();

	static Position Zero;
	float		x() const;
	float		y() const;
	float		z() const;

	void		SetX(const float value);
	void		SetY(const float value);
	void		SetZ(const float value);

	float		Distance(const Position& p) const;
	void		TranslateTo(const Vector& delta);
	void		MoveTo(const Position& position);

	bool		operator==(const Position& other) const;
	Position	operator+(const Position& other) const;
	Position	operator*(const float value) const;
	Position	operator/(const float value) const;
	Vector		operator-(const Position& other) const;

	std::size_t customHash() const override;
	bool operator==(const Hasheable& outra) const override;
};
// ---------------------------------------------------------------------------------
//inline

inline float	Position::x() const {return _x;}
inline float	Position::y() const {return _y;}
inline float	Position::z() const {return _z;}

inline void		Position::SetX(const float value) { _x = value; }
inline void		Position::SetY(const float value) { _y = value; }
inline void		Position::SetZ(const float value) { _z = value; }

inline bool		Position::operator==(const Position& other) const {
	return
		this->x() == other.x() &&
		this->y() == other.y() &&
		this->z() == other.z();
}


#endif