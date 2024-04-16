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

public:
    virtual ~Window() {}

    //virtual HINSTANCE AppId() const = 0;
    virtual HWND Id() const;
    virtual int Width() const ;
    virtual int Height() const;
    virtual WindowModes Mode() const ;
    virtual Position Center() const ;
    virtual std::string Title() const;
    virtual Color GetColor() const = 0;
    virtual void Icon(const uint icon) = 0;
    virtual void Cursor(const uint cursor) = 0;
    virtual void Title(const std::string title) = 0;
    virtual void Size(int width, int height) = 0;
    virtual void Mode(WindowModes mode) = 0;
    virtual void SetColor(Color color) = 0;
    virtual void HideCursor(bool hide) = 0;
    //virtual void Print(const std::string& text, int x, int y, COLORREF color = C_BLACK) = 0;
    virtual void Close() = 0;
    virtual void Clear() = 0;
    virtual bool Create() = 0;
    virtual void InFocus(void(*func)()) = 0;
    virtual void LostFocus(void(*func)()) = 0;

    virtual void isResizeable(bool value);
    virtual void PollEvents() const;
};

inline  HWND Window::Id() const { return 0; }
inline void Window::isResizeable(bool value) { this->_allowResize = value; }
inline void Window::PollEvents() const{}

inline int Window::Width() const {return _width;}
inline int Window::Height() const {return _height;}
inline WindowModes Window::Mode() const {return _mode;}
inline std::string Window::Title() const {return _title;}
inline Position Window::Center() const { return Position(_width / 2, _height / 2); }
#endif // WINDOW_H