#ifndef UT_GRAPHIC_CONTEXT_H
#define UT_GRAPHIC_CONTEXT_H

#include "Graphics.h"
#include "Window.h" 
#include "Input.h" 



class GraphicContext {
private:
	Graphics* _graphics = nullptr;
	Window* _window = nullptr;

public:

	GraphicContext(Graphics*, Window*);
	~GraphicContext();

	Graphics* graphics() const;
	Window* window() const;
};

inline Graphics* GraphicContext::graphics() const { return this->_graphics; }
inline Window* GraphicContext::window() const { return this->_window; }

#endif