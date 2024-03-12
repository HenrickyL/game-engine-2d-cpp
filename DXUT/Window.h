// Window.h
#ifndef DXUT_WINDOW_H
#define DXUT_WINDOW_H

#include "Types.h"      // tipos personalizados da biblioteca
#include <string>       // inclui a classe string
#include "Position.h"
//#include "Colors.h"
#include <wtypes.h>
using std::string;      // permite usar o tipo string sem std::

// ---------------------------------------------------------------------------------

// Global constants and enumerations

enum WindowModes { FULLSCREEN, WINDOWED, BORDERLESS };

// ---------------------------------------------------------------------------------

class Window {
public:
    virtual ~Window() {}

    //virtual HINSTANCE AppId() const = 0;
    virtual HWND Id() const = 0;
    virtual int Width() const = 0;
    virtual int Height() const = 0;
    virtual int Mode() const = 0;
    virtual Position Center() const = 0;
    virtual std::string Title() const = 0;
    virtual COLORREF Color() const = 0;
    virtual void Icon(const uint icon) = 0;
    virtual void Cursor(const uint cursor) = 0;
    virtual void Title(const std::string title) = 0;
    virtual void Size(int width, int height) = 0;
    virtual void Mode(WindowModes mode) = 0;
    virtual void Color(int r, int g, int b) = 0;
    virtual void HideCursor(bool hide) = 0;
    //virtual void Print(const std::string& text, int x, int y, COLORREF color = C_BLACK) = 0;
    virtual void Close() = 0;
    virtual void Clear() = 0;
    virtual bool Create() = 0;
    virtual void InFocus(void(*func)()) = 0;
    virtual void LostFocus(void(*func)()) = 0;
};

#endif // WINDOW_H