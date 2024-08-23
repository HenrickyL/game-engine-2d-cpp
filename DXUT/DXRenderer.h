#ifndef UT_DX_RENDERER_H
#define UT_DX_RENDERER_H

#include "Renderer.h"
#include "DXWindow.h"
#include "DXGraphics.h"
#include <DirectXMath.h>  // lib matemática do DirectX

// ---------------------------------------------------------------------------------
using namespace DirectX;

// definição de um vértice para o D3D
struct DXVertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
	XMFLOAT2 tex;
};


class DXRenderer : public Renderer {
public:
    DXRenderer();
    ~DXRenderer();
	void Draw(const Geometry& g) override;

    bool Initialize(Window* window, Graphics* graphics) override;
    void Draw(SpriteData& sprite) override;
    void Render() override;

    void BeginPixels();                                         // trava a textura de plotagem de pixels
    void EndPixels();                                           // destrava a textura de plotagem de pixels

private:
    DXWindow* _window;                          // ponteiro para janela do jogo
    DXGraphics* _graphics;                        // ponteiro para dispositivo gráfico

    ID3D11InputLayout* inputLayout;                 // input layout
    ID3D11VertexShader* vertexShader;                // vertex shader
    ID3D11PixelShader* pixelShader;                 // pixel shader
    ID3D11RasterizerState* rasterState;                 // estado do rasterizador
    ID3D11SamplerState* sampler;                     // estado do amostrador de textura
    ID3D11Buffer* vertexBuffer;                // buffer de vértices
    ID3D11Buffer* indexBuffer;                 // buffer de índices
    ID3D11Buffer* constantBuffer;              // buffer para o shader
    uint                    vertexBufferPosition;        // posição atual do vertex buffer

    static const uint MinBatchSize = 128;                   // tamanho mínimo do lote de sprites
    static const uint MaxBatchSize = 4096;                  // tamanho máximo do lote de sprites - Max 2^15
    static const uint VerticesPerSprite = 4;                // número de vértices por _sprite
    static const uint IndicesPerSprite = 6;                 // número de índices por _sprite

    // ----------------------------------------
    // Pixel Ploting
    // ----------------------------------------
    ID3D11Texture2D* pixelPlotTexture;                // textura para plotagem de pixels
    ID3D11ShaderResourceView* pixelPlotView;                   // visualização para a textura de pixels
    SpriteData                 pixelPlotSprite;                 // sprite para a textura de pixels
    long                       videoMemoryPitch;                // número de pixels em cada linha da memória de vídeo
    ulong* videoMemory;                     // ponteiro para a memória de vídeo (32 bits por pixel)

    void PlotPixel(int x, int y, Color color) const ;                  // plota pixels sem recorte (clipping)
    void PlotLine(int x, int y, int flag, Color color) const;         // plota pixels para algoritmo de linha
    void DrawLine(int a1, int b1, int a2, int b2, Color color) const; // desenha linha sem recorte (clipping)
    int  ClipLine(int& x1, int& y1, int& x2, int& y2) const;          // recorta linha para desenhar na viewport

                           // vetor de sprites

    // renderiza um grupo de sprites de mesma textura
    void RenderBatch(ID3D11ShaderResourceView* texture, SpriteData** sprites, uint cont);


	//--------------------------------------------------
	void DrawRect(const Rect& rect) const override;
	void DrawPoint(const Point& point)const override;
	void DrawLine(const Line& line)const override;
	void DrawCircle(const Circle& circle)const override;
	void DrawPolygon(const Poly& polygon)const override;
    void SwitchTypeGeometryToDraw(const Geometry& geometry) const override;
	//--------------------------------------------------
	
};
#endif