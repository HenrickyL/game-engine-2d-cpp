// Graphics.h
#ifndef UT_GRAPHICS_H
#define UT_GRAPHICS_H

#include "Window.h"
#include "Types.h"
#include "GraphicsFPS.h"


class Graphics {
protected:
    Window* window;
    float   viewportWidth, viewportHeight;
    FPSType currentFPS;
public:
    virtual ~Graphics() {}

    virtual void VSync(bool state) = 0;
    virtual void Clear() = 0;
    virtual void Present() = 0;
    virtual bool Initialize() = 0;

    virtual void SetViewportWidth(float width);
    virtual void SetViewportHeight(float height);
    virtual void SetFPS(FPSType fps);

    virtual float ViewportWidth() const;
    virtual float ViewportHeight() const;
    virtual FPSType FPS() const;
};

#endif // GRAPHICS_H
