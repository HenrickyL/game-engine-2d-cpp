#ifndef UT_GRAPHIC_CONTEXT_H
#define UT_GRAPHIC_CONTEXT_H

#include "Graphics.h"
#include "Window.h" 
#include "Input.h" 
#include "Renderer.h"


class GraphicContext {
private:
	Graphics* _graphics = nullptr;
	Window* _window = nullptr;
	Renderer* _renderer = nullptr;

public:

	GraphicContext(Graphics*, Window*, Renderer*);
	~GraphicContext();

	Graphics* graphics() const;
	Window* window() const;
	Renderer* renderer() const;
};

inline Graphics* GraphicContext::graphics() const { return this->_graphics; }
inline Window* GraphicContext::window() const { return this->_window; }
inline Renderer* GraphicContext::renderer() const { return this->_renderer; }


#endif