#ifndef DXUT_UTIL_SUBJECT_NOTIFICATION_H
#define DXUT_UTIL_SUBJECT_NOTIFICATION_H
#include <string>
//------------------------------------------
class SubjectNotification {
protected:
	std::string info;
public:
	virtual void Process() = 0;

};
#endif