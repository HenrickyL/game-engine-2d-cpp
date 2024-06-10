#ifndef UT_DIRTYABLE_H
#define UT_DIRTYABLE_H

/// TODO: Ver a necessidade dessa classe, talvez usar VertexBuffer pode ajudar
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