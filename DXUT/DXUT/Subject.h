#ifndef DXUT_UTIL_SUBJECT_H
#define DXUT_UTIL_SUBJECT_H
//------------------------------------------
#include<vector>
#include "SubjectNotification.h"
//------------------------------------------
template<class T>
class Observer;
//------------------------------------------
template<class T>
class Subject {
protected:
	std::vector<Observer<T>*>* observers;

public:
	virtual void Attach(Observer<T>* observer) = 0;
	virtual void Detach(Observer<T>* observer) = 0;
	virtual void NotifyObservers(SubjectNotification* notification) = 0;
};
#endif