#ifndef DXUT_RENDERER_H
#define DXUT_RENDERER_H
// ---------------------------------------------------------------------------------
#include "Window.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Geometry.h"
#include <vector>
#include <DirectXMath.h>                                        // tipos da biblioteca matemática do DirectX
using std::vector;
using namespace DirectX;
// ---------------------------------------------------------------------------------
enum FillModeEnum
{
    WIREFRAME = 2,
    SOLID = 3
};
// definição de um vértice para o D3D
struct Vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
    XMFLOAT2 tex;
};
// ---------------------------------------------------------------------------------
class Renderer
{
private:
    Window* _window;                          // ponteiro para janela do jogo
    Graphics* _graphics;                        // ponteiro para dispositivo gráfico

    ID3D11InputLayout*      inputLayout;                 // input layout
    ID3D11VertexShader*     vertexShader;                // vertex shader
    ID3D11PixelShader*      pixelShader;                 // pixel shader
    ID3D11RasterizerState*  rasterState;                 // estado do rasterizador
    ID3D11SamplerState*     sampler;                     // estado do amostrador de textura
    ID3D11Buffer*           vertexBuffer;                // buffer de vértices
    ID3D11Buffer*           indexBuffer;                 // buffer de índices
    ID3D11Buffer*           constantBuffer;              // buffer para o shader
    uint                    vertexBufferPosition;        // posição atual do vertex buffer
    FillModeEnum            _fillMode = SOLID;

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

    void PlotPixel(int x, int y, ulong color);                  // plota pixels sem recorte (clipping)
    void PlotLine(int x, int y, int flag, ulong color);         // plota pixels para algoritmo de linha
    void DrawLine(int a1, int b1, int a2, int b2, ulong color); // desenha linha sem recorte (clipping)
    int  ClipLine(int& x1, int& y1, int& x2, int& y2);          // recorta linha para desenhar na viewport

    vector<SpriteData*> spriteVector;                       // vetor de sprites

    // renderiza um grupo de sprites de mesma textura
    void RenderBatch(ID3D11ShaderResourceView* texture, SpriteData** sprites, uint cont);

public:
    Renderer();                                             // construtor
    ~Renderer();                                            // destrutor

    // ----------------------------------------
    // Pixel Ploting
    // ----------------------------------------
    void BeginPixels();                                         // trava a textura de plotagem de pixels
    void Draw(Geometry* shape, ulong color);                   // desenha geometria
    void Draw(Point* point, ulong color);                      // desenha ponto
    void Draw(Line* line, ulong color);                        // desenha linha  
    void Draw(Rect* rect, ulong color);                        // desenha retângulo  
    void Draw(Circle* circ, ulong color);                      // desenha círculo  
    void Draw(Poly* pol, ulong color);                         // desenha polígono
    void Draw(Mixed* mul, ulong color);                        // desenha formas mistas
    void EndPixels();                                           // destrava a textura de plotagem de pixels

    bool Initialize(Window* window, Graphics* graphics);  // inicializa o renderizador
    void Draw(SpriteData* sprite);                         // adiciona _sprite na lista
    void Render();                                          // envia sprites para desenho
    void SetFillMode(const FillModeEnum value);
};

// --------------------------------------------------------------------------------
// Funções Membro Inline
inline void Renderer::SetFillMode(const FillModeEnum mode)
{    _fillMode = mode; }

// plota pixels sem fazer recorte (clipping)
inline void Renderer::PlotPixel(int x, int y, ulong color)
{    videoMemory[x + y * videoMemoryPitch] = color;}

// plota pixels para o método de desenho de linhas
inline void Renderer::PlotLine(int x, int y, int flag, ulong color)
{   flag ? PlotPixel(y, x, color) : PlotPixel(x, y, color); }


#endif
