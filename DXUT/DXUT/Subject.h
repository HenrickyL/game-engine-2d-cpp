#ifndef DXUT_UTIL_SUBJECT_H
#define DXUT_UTIL_SUBJECT_H
//------------------------------------------
#include<vector>
#include "SubjectNotification.h"

//------------------------------------------
class Observer;
//------------------------------------------

class Subject {
protected:
	std::vector<Observer*>* observers;

public:
	Subject();

	void Attach(Observer* observer);
	void Detach(Observer* observer);
	void NotifyObservers(SubjectNotification* notification);
};
#endif