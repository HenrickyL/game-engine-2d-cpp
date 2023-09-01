#ifndef DXUT_UTIL_SUBJECT_H
#define DXUT_UTIL_SUBJECT_H
//------------------------------------------
#include<vector>
#include "SubjectNotification.h"
//------------------------------------------
template<class T>
class IObserver;
//------------------------------------------
template<class T>
class ISubject {
protected:
	std::vector<IObserver<T>*>* observers;

public:
	virtual void Attach(IObserver<T>* observer) = 0;
	virtual void Detach(IObserver<T>* observer) = 0;
	virtual void NotifyObservers(SubjectNotification* notification) = 0;
};
#endif