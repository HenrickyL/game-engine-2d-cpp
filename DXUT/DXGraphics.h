// DXGraphics.h
#ifndef UT_DXGRAPHICS_H
#define UT_DXGRAPHICS_H

#include "Graphics.h"
#include "Window.h"
#include <d3d11.h>


class DXGraphics : public Graphics {
private:
    Window* window;
    IDXGISwapChain* swapChain;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11BlendState* blendState;
    D3D_FEATURE_LEVEL featureLevel;
    float bgColor[4];
    bool vSync;
    float viewportWidth, viewportHeight;
    FPSType currentFPS;


public:
    static ID3D11Device* device;                            // dispositivo gráfico
    static ID3D11DeviceContext* context;                    // contexto do dispositivo gráfico
    static D3D11_VIEWPORT        viewport;                  // viewport

    DXGraphics(Window* window);
    ~DXGraphics();

    void VSync(bool state) override;
    void Clear() override;
    void Present() override;
    bool Initialize() override;
    void SetViewportWidth(float width) override;
    void SetViewportHeight(float height) override;
    float ViewportWidth() const override;
    float ViewportHeight() const override;
    void SetFPS(FPSType fps) override;
    FPSType FPS() const override;
};

#endif // DXGRAPHICS_H
