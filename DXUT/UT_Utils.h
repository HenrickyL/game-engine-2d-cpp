#ifndef UT_UTILS_H
#define UT_UTILS_H


class RandomUtils {
public:
	static float GetRandomFloat(float min, float max);
	static int GetRandomInt(int min, int max);

};

// ---------------------------------------------------------------------------
template<typename Base, typename T>
inline bool instanceOf(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

//template<typename Base, typename T>
//inline Base* getInstanceOf(T* ptr) {
//	return dynamic_cast<Base*>(ptr);
//}

#endif