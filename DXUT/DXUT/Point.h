#ifndef DXUT_POINT_H
#define DXUT_POINT_H
// ---------------------------------------------------------------------------------
class Vector;
// ---------------------------------------------------------------------------------

class Point
{
protected:
	float _x=0, _y=0,_z=0;
public:
	Point();
	Point(float x, float y, float z=0);
	Point(Point* p);
	~Point();

	float X() const;
	float Y() const;
	float Z() const;

	void SetX(const float value);
	void SetY(const float value);
	void SetZ(const float value);

	float Distance(Point* p);
	Point Translate(const Point delta);
	void MoveTo(const Point position);

	Point	operator+(const Point& other) const;
	Point	operator*(const float value) const;
	Vector	operator-(const Point& other) const;

};
// ---------------------------------------------------------------------------------
//inline

inline float Point::X() const {return _x;}
inline float Point::Y() const {return _y;}
inline float Point::Z() const {return _z;}

inline void Point::SetX(const float value) { _x = value; }
inline void Point::SetY(const float value) { _y = value; }
inline void Point::SetZ(const float value) { _z = value; }



#endif