 // Window.h
#ifndef DXUT_WINDOW_H
#define DXUT_WINDOW_H

#include "Types.h"      // tipos personalizados da biblioteca
#include <string>       // inclui a classe string
#include "Position.h"
#include "Color.h"
#include <wtypes.h>
using std::string;      // permite usar o tipo string sem std::

// ---------------------------------------------------------------------------------

// Global constants and enumerations

enum WindowModes { FULLSCREEN, WINDOWED, BORDERLESS };

// ---------------------------------------------------------------------------------
class Window {
protected:
    int             _windowMode;
    int             _width = 800;
    int             _height = 600;
    Position        _center;
    WindowModes     _mode = WINDOWED;
    int             _windowPosX;
    int             _windowPosY;
    string          _title = "Title";
    Color           _color = Color::BLACK;
    bool            _allowResize = false;
    bool            _onCreate = false;
    bool            _isCursorDisable = false;
    //perspective
    double _fovy = 45.0f; //angle degree
    double _aspect = 0; //proporsion
    double _zNear = 0.1f;
    double _zFar = 500.0f;

    void UpdateAspect();


public:
    virtual ~Window() = default;

    //virtual HINSTANCE AppId() const = 0;
    virtual HWND Id() const;
    virtual int Width() const ;
    virtual int Height() const;
    virtual WindowModes Mode() const ;
    virtual Position Center() const ;
    virtual std::string Title() const;
    virtual Color GetColor() const = 0;
    virtual bool isCursorDisable()const;

    virtual void SetCursorDisable(bool value);
    virtual void Icon(const uint icon) = 0;
    virtual void Cursor(const uint cursor) = 0;
    virtual void SetTitle(const std::string title) = 0;
    virtual void Size(int width, int height);
    virtual void Mode(WindowModes mode) = 0;
    virtual void SetColor(Color color);
    virtual void HideCursor(bool hide) = 0;
    //virtual void Print(const std::string& text, int x, int y, COLORREF color = C_BLACK) = 0;
    virtual void Close() = 0;
    virtual void Clear() = 0;
    virtual bool Create() = 0;
    virtual bool ShouldClose() const = 0;

    virtual void InFocus(void(*func)()) = 0;
    virtual void LostFocus(void(*func)()) = 0;

    virtual void isResizeable(bool value);
    virtual void PollEvents() = 0;

    double fovy()const;
    double aspect()const;
    double zNear() const;
    double zFar()const;

    void SetFovy(double value);
    void SetNear(double value);
    void SetFar(double value);

};

#endif // WINDOW_H