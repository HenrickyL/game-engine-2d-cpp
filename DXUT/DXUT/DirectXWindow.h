// DirectXWindow.h
#ifndef DXUT_DIRECTXWINDOW_H
#define DXUT_DIRECTXWINDOW_H


// ---------------------------------------------------------------------------------
// includes
#include "Window.h"
#include <windows.h>    // inclui funções do windows
#include <windowsx.h>   // inclui extensões do windows

// ---------------------------------------------------------------------------------

class DirectXWindow : public Window {
private:
    HINSTANCE   hInstance;                                  // identificador da aplicação
    HDC			windowHdc;									// contexto do dispositivo
    RECT		windowRect;									// área cliente da janela
    HWND		windowId;                                   // identificador da janela
    int			windowWidth;                                // largura da janela
    int			windowHeight;                               // altura da janela
    HICON		windowIcon;                                 // ícone da janela
    HCURSOR		windowCursor;                               // cursor da janela
    COLORREF	windowColor;                                // cor de fundo da janela
    string		windowTitle;                                // nome da barra de título
    DWORD		windowStyle;                                // estilo da janela 
    int			windowMode;                                 // modo tela cheia, em janela ou sem borda
    int			windowPosX;                                 // posição inicial da janela no eixo x
    int			windowPosY;                                 // posição inicial da janela no eixo y
    Position       center;

    //function reference
    static void (*inFocus)();								// executar quando a janela ganhar de volta o foco
    static void (*lostFocus)();								// executar quando a janela perder o foco


public:
    DirectXWindow();                                               // construtor
    ~DirectXWindow();												// destrutor

    HINSTANCE AppId() const override;                                      // retorna o identificador da aplicação
    HWND Id() const override;                                         // retorna o identificador da janela
    int Width() const override;                                       // retorna a largura atual da janela
    int Height() const override;                                      // retorna a altura atual da janela
    int Mode() const override;                                        // retorna o modo atual da janela (FULLSCREEN/WINDOWED)

    Position Center() const override;

    std::string Title() const override;                               // retorna título da janela
    COLORREF Color() const override;                                   // retorna a cor de fundo da janela

    void Icon(const uint icon) override;                              // define o ícone da janela
    void Cursor(const uint cursor) override;                          // define o cursor da janela
    void Title(const std::string title) override;                     // define o título da janela 
    void Size(int width, int height) override;                        // define o tamanho (largura e altura) da janela
    void Mode(WindowModes mode) override;                                    // define o modo da janela (FULLSCREEN/WINDOWED)
    void Color(int r, int g, int b) override;                         // define a cor de fundo da janela

    void HideCursor(bool hide) override;                              // habilita ou desabilita a exibição do cursor
    //void Print(const std::string& text, int x, int y, COLORREF color = C_BLACK) override;  // mostra texto na janela	
    void Close() override;                                            // fecha a janela e sai do jogo
    void Clear() override;                                            // limpa a área cliente
    bool Create() override;                                           // cria a janela com os valores dos atributos	

    void InFocus(void(*func)()) override;                             // altera função executada ao ganhar foco
    void LostFocus(void(*func)()) override;                           // altera função executada na perda de foco

    // tratamento de eventos do Windows
    static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

// ---------------------------------------------------------------------------------

// Inline Member Functions
// retorna identificador da aplicação
inline HINSTANCE DirectXWindow::AppId() const
{
    return hInstance;
}
// retorna o identificador da janela do jogo
inline HWND DirectXWindow::Id() const
{
    return windowId;
}
// retorna a largura atual da janela
inline int DirectXWindow::Width() const
{
    return windowWidth;
}

// retorna a altura atual da janela
inline int DirectXWindow::Height() const
{
    return windowHeight;
}

// retorna o modo atual da janela (FULLSCREEN/WINDOWED)
inline int DirectXWindow::Mode() const
{
    return windowMode;
}


// retorna título da janela
inline string DirectXWindow::Title() const
{
    return windowTitle;
}

// retorna a cor de fundo da janela
inline COLORREF DirectXWindow::Color() const
{
    return windowColor;
}

inline Position DirectXWindow::Center() const
{
    return center;
}


// ----------------------------------------------------------

// define o ícone da janela
inline void DirectXWindow::Icon(const uint icon)
{
    windowIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(icon));
}
// define o cursor da janela
inline void DirectXWindow::Cursor(const uint cursor)
{
    windowCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(cursor));
}

// define o título da janela 
inline void DirectXWindow::Title(const string title)
{
    windowTitle = title;
}

// define a cor de fundo da janela
inline void DirectXWindow::Color(int r, int g, int b)
{
    windowColor = RGB(r, g, b);
}

// ----------------------------------------------------------

// habilita ou desabilita a exbição do cursor
inline void DirectXWindow::HideCursor(bool hide)
{
    ShowCursor(!hide);
}

// fecha a janela e sai do jogo 
inline void DirectXWindow::Close()
{
    PostMessage(windowId, WM_DESTROY, 0, 0);
}

// limpa a área cliente
inline void DirectXWindow::Clear()
{
    //FillRect(windowHdc, &windowRect, CreateSolidBrush(Color()));
    InvalidateRect(Id(), NULL, TRUE);
}


// ---------------------------------------------------------------------------------

// altera função executada no ganho de foco
inline void DirectXWindow::InFocus(void(*func)())
{
    inFocus = func;
}

// altera função executada na perda de foco
inline void DirectXWindow::LostFocus(void(*func)())
{
    lostFocus = func;
}
// ---------------------------------------------------------------------------------
#endif