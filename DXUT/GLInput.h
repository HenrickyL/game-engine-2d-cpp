#ifndef DXUT_GLINPUT_H
#define DXUT_GLINPUT_H

#include "Input.h"
#include "GLWindow.h"

typedef void(*GLKeyCallbackType)(GLFWwindow*, int, int, int, int);

class GLInput : public Input {
private:
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
public:
	GLInput();
	void  Read() override;
	static GLKeyCallbackType keyCallbackPtr;

	static void InputKeysProc(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#endif