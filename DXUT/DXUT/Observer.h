#ifndef DXUT_UTIL_OBSERVER_H
#define DXUT_UTIL_OBSERVER_H
//------------------------------------------
#include<vector>
#include "SubjectNotification.h"
//------------------------------------------
class Subject;
//------------------------------------------

class Observer {
protected:

public:
	virtual void Notify(SubjectNotification* notification) = 0;
};
#endif