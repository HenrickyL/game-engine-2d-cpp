#ifndef UT_DIRTYABLE_H
#define UT_DIRTYABLE_H

class Dirtyable {
private:
	bool _isDirt = true;
public:
	virtual bool isDirty()const;
	virtual void SetDirt();
	virtual void Clear();
};


inline bool Dirtyable::isDirty()const {return _isDirt;}
inline void Dirtyable::SetDirt() {_isDirt = true;}
inline void Dirtyable::Clear() {_isDirt = false;}

#endif