#ifndef DXUT_SPRITE_H
#define DXUT_SPRITE_H
// ---------------------------------------------------------------------------------
#include "Image.h"
#include "DXUT_Utils_Direction_.h"
// ---------------------------------------------------------------------------------
struct SpriteData
{
    float x, y;
    float scale;
    float depth;
    float rotation;
    float xAnchor;
    float yAnchor;
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
    Image* image;            // ponteiro para uma imagem

    const float scaleDefault = 1.0f,
		rotationDefault = 0.0f;

public:
    Sprite(string filename);        // constroi _sprite a partir de um arquivo
    Sprite(Image* img);      // constroi _sprite a partir de imagem existente
    ~Sprite();                      // destrutor do _sprite

    int Width();                    // largura do _sprite
    int Height();                   // altura do _sprite

    // desenha imagem na posição (x,y) e profundidade (z)
    void Draw(float x, float y, float z = Layer::MIDDLE);

    // ---------------------------------------------------------------------------------
    void ResetSprite();

    void SetRotation(Direction rotation);
    void SetRotation(float rotation);
    void SetScale(float scale);
    void SetAnchor(float x, float y);
    void SetImage(Image* img);
    void SetImage(const std::string _filename);


    float Rotation() const;
    float Scale() const;


};

// ---------------------------------------------------------------------------------
// Funções Inline

// retorna a largura do _sprite
inline int Sprite::Width()
{
    return image->Width() * sprite.scale;
}

// retorna a altura do _sprite
inline int Sprite::Height()
{
    return image->Height() * sprite.scale;
}

// ---------------------------------------------------------------------------------
inline void Sprite::SetRotation(Direction rotation)
{
    sprite.rotation = DirectionConverter::GetRadians(rotation);
}

inline void Sprite::SetRotation(float rotation)
{
    sprite.rotation = rotation;
}

inline void Sprite::SetScale(float scale)
{
    sprite.scale = scale;
}

inline float Sprite::Rotation() const
{
    return sprite.rotation;
}

inline float Sprite::Scale() const
{
    return sprite.scale;
}

inline void Sprite::SetAnchor(float x, float y)
{
    sprite.xAnchor = x;
    sprite.yAnchor = y;
}


#endif
