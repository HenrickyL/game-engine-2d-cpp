#ifndef DXUT_TEST_OBSERVER
#define DXUT_TEST_OBSERVER
#include "DXUT_Observer.h"
#include <debugapi.h>

#include "Instance.h"


//Define Perceptions
class PerceptionNotification : public SubjectNotification
{
public:
	PerceptionNotification()
	{
		info = "Perception";
	}
};


class See : public PerceptionNotification{
public:
	See()
	{
		info += " - See\n";
	}
	void Process() override
	{
		OutputDebugString(info.c_str());
	}
};
class Hear : public PerceptionNotification
{
	
public:
	Hear()
	{
		info += " - Hear\n";
	}
	void Process() override
	{
		OutputDebugString(info.c_str());
	}
};
// Define Observers

class Hero : public Observer<PerceptionNotification>
{
	void Notify(SubjectNotification* notification) override
	{
		if (instanceOf<See>(notification))
		{
			OutputDebugString("\nHero:\n\t");
			notification->Process();
		}
	}
};
class Enemy : public Observer<PerceptionNotification>
{
	void Notify(SubjectNotification* notification) override
	{
		if (instanceOf<Hear>(notification))
		{
			OutputDebugString("\nEnemy:\n\t");
			notification->Process();
		}
	}
};

class Fase : public Subject<PerceptionNotification>{

public:
	Fase()
	{
		observers = new std::vector<Observer<PerceptionNotification>*>();
	}

	void Attach(Observer<PerceptionNotification>* observer) override
	{
		observers->push_back(observer);
	}
	void Detach(Observer<PerceptionNotification>* observer) override
	{
		for (auto it = observers->begin(); it != observers->end(); ++it) {
			if (*it == observer) {
				observers->erase(it);
				break;
			}
		}
	}
	void NotifyObservers(SubjectNotification* notification) override
	{
		for (size_t i = 0; i < observers->size(); i++) {
			observers->at(i)->Notify(notification);
		}
	}
	
};
#endif