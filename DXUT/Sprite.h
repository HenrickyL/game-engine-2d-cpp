#ifndef DXUT_SPRITE_H
#define DXUT_SPRITE_H
// ---------------------------------------------------------------------------------
#include "Image.h"
#include "DXUT_Utils_Direction_.h"
#include "Position.h"
#include "Geometry.h"
#include "Color.h"
#include "Movable.h"
// ---------------------------------------------------------------------------------
struct SpriteData
{
    Position position = Position::Zero;
    Vector scales = Vector::One;
    float scale = 1.0f;
    float depth;
    Vector rotation = Vector::Zero;
    Position anchor = Position::Zero;
    Color color;
    Image* image;
    float width = 1.0f;
    float height = 1.0f;
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
class Sprite : public Movable
{
private:
    SpriteData* _sprite;              // dados do _sprite
    bool _localImage;                // imagem local ou externa
    Image* _image;                   // ponteiro para uma imagem

    const Vector _scaleDefault = Vector::One;

public:
    Sprite(Image* img);             // constroi _sprite a partir de imagem existente
    ~Sprite();                      // destrutor do _sprite

    // desenha imagem na posição (x,y) e profundidade (z)
    void    Draw();

    // ---------------------------------------------------------------------------------

    void    ResetSprite();

    void    SetRotationZ(Direction rotation);
    void    SetRotation(Vector rotation);
    void    SetScales(Vector scale);
    void    SetScale(float scale);

    void    SetImage(Image* img);
    void    SetLayer(float layer);
    void    SetOpacity(float value);
    void    SetFilterColor(Color color);


    Vector   Rotation() const;
    Vector   Scale() const;
    float   Width() const;                    // largura do _sprite
    float   Height() const;                   // altura do sprite
    float   HalfWidth() const;
    float   HalfHeight() const;
    Rect*    GetRect() const;
    Circle*  GetCircle() const;
    Color   GetFilterColor() const;
    SpriteData* data() const;

    void MoveTo(const Position& position) override;
    void MoveTo(Position* position) override;
    void TranslateTo(const Vector& delta) override;

};

#endif
