#include "Sprite.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicialização de membros estáticos das classes
const float Layer::FRONT    = 0.00f;
const float Layer::UPPER    = 0.25f;
const float Layer::MIDDLE   = 0.50f;
const float Layer::LOWER    = 0.75f;
const float Layer::BACK     = 0.99f;
// ---------------------------------------------------------------------------------


Sprite::Sprite(Image* img): Movable(Position::Zero)
{
    // aponta para imagem externa
    _image = img;
    _localImage = false;
    // configura registro sprite
    ResetSprite();

}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{  
    if (_sprite)
        delete _sprite;
    if (_localImage)
        delete _image;
}

// ---------------------------------------------------------------------------------


void Sprite::ResetSprite()
{
    if (_sprite == nullptr) {
        _sprite = new SpriteData();
    }
    _sprite->image = _image;
    _sprite->width = _image->width();
    _sprite->height = _image->height();
    _sprite->scale = _scaleDefault;
    _sprite->depth = Layer::MIDDLE;
    _sprite->rotation = _rotationDefault;
    _sprite->anchorX = Width() / 2;
    _sprite->anchorY = Height() / 2;
    _sprite->color = Color();
    _sprite->position = position();
}


void Sprite::Draw()
{
    //adiciona o sprite na lista de desenho
    if(this != nullptr)
    Engine::renderer->Draw(*_sprite);
}

// ---------------------------------------------------------------------------------

void Sprite::SetImage(Image* img)
{
    if (img->filename() != _image->filename()) {
        _image = img;
        _sprite->image = _image;
        _sprite->width = _image->width();
        _sprite->height = _image->height();
    }
}

// ---------------------------------------------------------------------------------

Rect*  Sprite::GetRect() const 
{ 
    float w = HalfWidth();
    float h = HalfHeight();
    float Ax = position().x() - w;
    float Ay = position().y() - h;
    float Bx = position().x() + w;
    float By = position().y() + h;
    return new Rect(Position(Ax, Ay), Position(Bx, By));
}

Circle*  Sprite::GetCircle() const 
{
    float r = (HalfHeight() + HalfWidth()) / 2;
    return new Circle(Position::Zero , r);
}

// ---------------------------------------------------------------------------------

void Sprite::MoveTo(const Position& position) {
    Movable::MoveTo(position);
    this->_sprite->position.MoveTo(position);
}
void Sprite::MoveTo(Position* position) {
    Movable::MoveTo(position);
    this->_sprite->position.MoveTo(position);

}
void Sprite::TranslateTo(const Vector& delta) {
    Movable::TranslateTo(delta);
    this->_sprite->position.TranslateTo(delta);
}

float    Sprite::Width() const { return _image->width() * _sprite->scale; }
float    Sprite::Height() const { return _image->height() * _sprite->scale; }
float    Sprite::HalfWidth() const { return Width() / 2.0f; }
float    Sprite::HalfHeight() const { return Height() / 2.0f; }
Color    Sprite::GetFilterColor() const { return _sprite->color; };

void Sprite::SetRotation(Direction rotation) { _sprite->rotation = DirectionConverter::GetRadians(rotation); }
void Sprite::SetRotation(float rotation) { _sprite->rotation = rotation; }
void Sprite::SetScale(float scale) { _sprite->scale = scale; }
void Sprite::SetLayer(float layer) { _sprite->depth = layer; }
void Sprite::SetOpacity(float value) { _sprite->color.setAlpha(value); }
void Sprite::SetFilterColor(Color color) { _sprite->color = color; }

float Sprite::Rotation() const { return _sprite->rotation; }
float Sprite::Scale() const { return _sprite->scale; }