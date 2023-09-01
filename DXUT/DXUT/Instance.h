#ifndef DXUT_UTILS_INSTANCE_OF_H
#define DXUT_UTILS_INSTANCE_OF_H

template<typename Base, typename T>
inline bool instanceOf(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}
#endif