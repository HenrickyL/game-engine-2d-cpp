#include "Observer.h"

void Observer::Notify(const SubjectNotification& notification) {
	notification.process();
}
