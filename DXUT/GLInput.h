#ifndef DXUT_GLINPUT_H
#define DXUT_GLINPUT_H

#include "Input.h"
#include "GLWindow.h"

typedef void(*GLKeyCallbackType)(GLFWwindow*, int, int, int, int);

class GLInput : public Input {
private:
public:
	static GLKeyCallbackType keyCallbackPtr;

	static void InputKeysCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void InputMousePositionCallback(GLFWwindow* window, int button, int action, int mods);

	static InputKeys GetKey(int key);

};
#endif