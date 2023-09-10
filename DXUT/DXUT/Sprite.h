#ifndef DXUT_SPRITE_H
#define DXUT_SPRITE_H
// ---------------------------------------------------------------------------------
#include "Image.h"
#include "DXUT_Utils_Direction_.h"
#include "Position.h"
#include "Geometry.h"
#include "Colors.h"
// ---------------------------------------------------------------------------------
struct SpriteData
{
    Position* position;
    float scale;
    float depth;
    float rotation;
    float anchorX = 0, anchorY = 0;
    Color color;
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
    Position* _position;
    bool localImage;                // imagem local ou externa
    Image* image;                   // ponteiro para uma imagem

    const float scaleDefault = 1.0f,
				rotationDefault = 0.0f;

public:
    Sprite(string filename);        // constroi _sprite a partir de um arquivo
    Sprite(Image* img);             // constroi _sprite a partir de imagem existente
    ~Sprite();                      // destrutor do _sprite

    // desenha imagem na posição (x,y) e profundidade (z)
    void    Draw();

    // ---------------------------------------------------------------------------------

    void    ResetSprite();

    void    SetRotation(Direction rotation);
    void    SetRotation(float rotation);
    void    SetScale(float scale);
    void    SetImage(Image* img);
    void    SetImage(const std::string _filename);
    void    SetPosition(const Position& p);
    void    SetLayer(float layer);
    void    SetOpacity(float value);
    void    SetFilterColor(Color color);


    float   Rotation() const;
    float   Scale() const;
    float   Width() const;                    // largura do _sprite
    float   Height() const;                   // altura do sprite
    float   HalfWidth() const;
    float   HalfHeight() const;
    Rect*   GetRect() const;
    Circle* GetCircle() const;
    Color   GetFilterColor() const;
    Position*  GetPosition() const;

};

// ---------------------------------------------------------------------------------
// Funções Inline

inline float        Sprite::Width() const { return image->Width() * sprite.scale;}
inline float        Sprite::Height() const { return image->Height() * sprite.scale;}
inline Position*    Sprite::GetPosition() const { return _position; }
inline float        Sprite::HalfWidth() const { return Width() / 2.0f; }
inline float        Sprite::HalfHeight() const { return Height() / 2.0f; }
inline Color        Sprite::GetFilterColor() const { return sprite.color; };

// ---------------------------------------------------------------------------------

inline void Sprite::SetRotation(Direction rotation) { sprite.rotation = DirectionConverter::GetRadians(rotation); }
inline void Sprite::SetRotation(float rotation) { sprite.rotation = rotation;}
inline void Sprite::SetScale(float scale) { sprite.scale = scale; }
inline void Sprite::SetLayer(float layer) { sprite.depth = layer; }
inline void Sprite::SetOpacity(float value) { sprite.color.A = max(0.0f, min(1.0f, value)); }
inline void Sprite::SetFilterColor(Color color) { sprite.color = color; }

// ---------------------------------------------------------------------------------

inline float Sprite::Rotation() const { return sprite.rotation;}

inline float Sprite::Scale() const { return sprite.scale;}

#endif
