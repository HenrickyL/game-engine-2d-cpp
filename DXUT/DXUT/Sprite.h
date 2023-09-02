#ifndef DXUT_SPRITE_H
#define DXUT_SPRITE_H
// ---------------------------------------------------------------------------------
#include "Image.h"
// ---------------------------------------------------------------------------------
struct SpriteData
{
    float x, y;
    float scale;
    float depth;
    float rotation;
    uint  width;
    uint  height;
    ID3D11ShaderResourceView* texture;
};
// ---------------------------------------------------------------------------------
struct Layer
{
    static const float FRONT;
    static const float UPPER;
    static const float MIDDLE;
    static const float LOWER;
    static const float BACK;
};
// ---------------------------------------------------------------------------------
class Sprite
{
private:
    SpriteData sprite;              // dados do _sprite 
    bool localImage;                // imagem local ou externa
    const Image* image;            // ponteiro para uma imagem

public:
    Sprite(string filename);        // constroi _sprite a partir de um arquivo
    Sprite(const Image* img);      // constroi _sprite a partir de imagem existente
    ~Sprite();                      // destrutor do _sprite

    int Width();                    // largura do _sprite
    int Height();                   // altura do _sprite

    // desenha imagem na posição (x,y) e profundidade (z)
    void Draw(float x, float y, float z = Layer::MIDDLE);
};

// ---------------------------------------------------------------------------------
// Funções Inline

// retorna a largura do _sprite
inline int Sprite::Width()
{
    return image->Width();
}

// retorna a altura do _sprite
inline int Sprite::Height()
{
    return image->Height();
}

// ---------------------------------------------------------------------------------

#endif
