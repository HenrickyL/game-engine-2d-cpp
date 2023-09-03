#ifndef DXUT_POINT_H
#define DXUT_POINT_H
// ---------------------------------------------------------------------------------
class Point
{
private:
	float _x, _y,_z;
public:
	Point();
	Point(float x, float y, float z);
	float X() const;
	float Y() const;
	float Z() const;

	void SetX(float value);
	void SetY(float value);
	void SetZ(float value);

	float Distance(Point* p);
};
// ---------------------------------------------------------------------------------
//inline

inline float Point::X() const {return _x;}
inline float Point::Y() const {return _y;}
inline float Point::Z() const {return _z;}

inline void Point::SetX(float value) { _x = value; }
inline void Point::SetY(float value) { _y = value; }
inline void Point::SetZ(float value) { _z = value; }

#endif