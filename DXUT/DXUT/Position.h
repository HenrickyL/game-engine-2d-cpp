#ifndef DXUT_POSITION_H
#define DXUT_POSITION_H
// ---------------------------------------------------------------------------------
class Vector;
// ---------------------------------------------------------------------------------

class Position
{
protected:
	float _x=0, _y=0,_z=0;
public:
	Position();
	Position(float x, float y, float z=0);
	Position(Position* p);
	~Position();

	float		X() const;
	float		Y() const;
	float		Z() const;

	void		SetX(const float value);
	void		SetY(const float value);
	void		SetZ(const float value);

	float		Distance(const Position& p) const;
	void		Translate(const Vector& delta);
	void		MoveTo(const Position& position);

	Position	operator+(const Position& other) const;
	Position	operator*(const float value) const;
	Vector		operator-(const Position& other) const;

};
// ---------------------------------------------------------------------------------
//inline

inline float	Position::X() const {return _x;}
inline float	Position::Y() const {return _y;}
inline float	Position::Z() const {return _z;}

inline void		Position::SetX(const float value) { _x = value; }
inline void		Position::SetY(const float value) { _y = value; }
inline void		Position::SetZ(const float value) { _z = value; }

#endif