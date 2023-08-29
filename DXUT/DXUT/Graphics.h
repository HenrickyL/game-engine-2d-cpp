#ifndef DXUT_GRAPHICS_H
#define DXUT_GRAPHICS_H

// --------------------------------------------------------------------------------
// Inclus�es

#include <dxgi.h>            // infraestrutura gr�fica do DirectX
#include <d3d11.h>           // principais fun��es do Direct3D
#include "Window.h"          // cria e configura uma janela do Windows
#include "Types.h"           // tipos espec�ficos da engine

// --------------------------------------------------------------------------------

class Graphics
{
private:
    Window* window;
    IDXGISwapChain* swapChain;                 // swap chain             
    ID3D11RenderTargetView* renderTargetView;          // render target view do backbuffer
    ID3D11BlendState* blendState;                // configura��o da mistura de cores
    D3D_FEATURE_LEVEL            featureLevel;              // n�vel de recursos D3D suportados pelo hardware
    float                        bgColor[4];                // cor de fundo do backbuffer
    bool                         vSync;                     // vertical sync 
    float   viewportWidth, viewportHeight;

public:
    Graphics(Window* window);                                             // constructor
    ~Graphics();                                            // destructor

    static ID3D11Device* device;                    // dispositivo gr�fico
    static ID3D11DeviceContext* context;                   // contexto do dispositivo gr�fico
    static D3D11_VIEWPORT        viewport;                  // viewport

    void VSync(bool state);                                 // liga/desliga vertical sync
    void Clear();                                           // limpa o backbuffer com a cor de fundo
    void Present();                                         // apresenta desenho na tela
    bool Initialize();                       // inicializa o Direct3D


    void SetViewportWidth(float width);
    void SetViewportHeight(float height);
    float ViewportWidth() const;
    float ViewportHeight() const;


};

// --------------------------------------------------------------------------------
// M�todos Inline
inline void Graphics::SetViewportWidth(float width) {
    this->viewportWidth = width;
}

inline void Graphics::SetViewportHeight(float height) {
    this->viewportHeight = height;
}

inline float Graphics::ViewportWidth() const{
    return this->viewportWidth;
}

inline float Graphics::ViewportHeight() const {
    return this->viewportHeight;
}


// liga/desliga vertical sync
inline void Graphics::VSync(bool state)
{
    vSync = state;
}

// limpa o bacbuffer para o pr�ximo quadro
inline void Graphics::Clear()
{
    context->ClearRenderTargetView(renderTargetView, bgColor);
}

// apresenta desenho na tela (troca backbuffer com frontbuffer)
inline void Graphics::Present()
{
    swapChain->Present(vSync, NULL);
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

// --------------------------------------------------------------------------------

#endif