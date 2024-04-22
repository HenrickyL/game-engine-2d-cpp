#include "GraphicContext.h"


GraphicContext::GraphicContext(Graphics* graphic, Window* window) : 
	_graphics(graphic), _window(window){}


GraphicContext::~GraphicContext() {
	if(_graphics)delete _graphics;
	if(_window)delete _window;
}