#include "Subject.h"
//------------------------------------------
#include "Observer.h"
//------------------------------------------

Subject::Subject() {
    observers = new std::vector<Observer*>();
}


void Subject::Attach(Observer* observer) {
	observers->push_back(observer);
}
void Subject::Detach(Observer* observer) {
    for (auto it = observers->begin(); it != observers->end(); ++it) {
        if (*it == observer) {
            observers->erase(it);
            break;
        }
    }
}

void Subject::NotifyObservers(SubjectNotification* notification) {
    for (size_t i = 0; i < observers->size(); i++) {
        observers->at(i)->Notify(notification);
    }
}