#include "GraphicContext.h"


GraphicContext::GraphicContext(Graphics* graphic, Window* window, Renderer* renderer) :
	_graphics(graphic), _window(window), _renderer(renderer) {}


GraphicContext::~GraphicContext() {
	if(_graphics)delete _graphics;
	if(_window)delete _window;
	if(_renderer)delete _renderer;
}