#include "GraphicContext.h"


GraphicContext::GraphicContext(Graphics* graphic, Window* window) : 
	_graphics(graphic), _window(window){}


GraphicContext::~GraphicContext() {
	delete _graphics;
	delete _window;
}