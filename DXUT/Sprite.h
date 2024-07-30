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
    Position position;
    float scale;
    float depth;
    float rotation;
    float anchorX = 0, anchorY = 0;
    Color color;
    uint  width;
    uint  height;
    Image* image;
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

    const float _scaleDefault = 1.0f,
				_rotationDefault = 0.0f;

public:
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
    void    SetLayer(float layer);
    void    SetOpacity(float value);
    void    SetFilterColor(Color color);


    float   Rotation() const;
    float   Scale() const;
    float   Width() const;                    // largura do _sprite
    float   Height() const;                   // altura do sprite
    float   HalfWidth() const;
    float   HalfHeight() const;
    Rect*    GetRect() const;
    Circle*  GetCircle() const;
    Color   GetFilterColor() const;

    void MoveTo(const Position& position) override;
    void MoveTo(Position* position) override;
    void TranslateTo(const Vector& delta) override;

};

#endif
