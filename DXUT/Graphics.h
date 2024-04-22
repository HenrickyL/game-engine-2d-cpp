// Graphics.h
#ifndef UT_GRAPHICS_H
#define UT_GRAPHICS_H

#include "Window.h"
#include "Types.h"
#include "GraphicsFPS.h"


enum GraphicType {
    T_2D,
    T_3D
};

class Graphics {
protected:
    Window* _window;
    float   _viewportWidth, _viewportHeight;
    FPSType _currentFPS;

    //perspective 3d
    static double _fovy; //angle degree
    static double _aspect; //proporsion
    static double _zNear;
    static double _zFar;

    GraphicType _type = T_3D;

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

    void SetType(GraphicType value);
    GraphicType type() const;

};

inline GraphicType Graphics::type() const { return this->_type; }
inline void Graphics::SetType(GraphicType value) { this->_type = value; }

#endif // GRAPHICS_H
