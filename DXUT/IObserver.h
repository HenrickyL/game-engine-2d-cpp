#ifndef DXUT_UTIL_OBSERVER_H
#define DXUT_UTIL_OBSERVER_H
//------------------------------------------
#include "SubjectNotification.h"
//------------------------------------------
template<class T>
class IObserver {
public:
	virtual void Notify(SubjectNotification* notification)=0;
};
#endif