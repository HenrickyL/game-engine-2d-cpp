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

Sprite::Sprite(string filename): Movable(Position::Zero)
{
    // carrega imagem
    _image = new Image(filename);
    _localImage = true;
    // configura registro sprite
    ResetSprite();
}

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
    _sprite->texture = _image->View();
    _sprite->width = _image->Width();
    _sprite->height = _image->Height();
    _sprite->scale = _scaleDefault;
    _sprite->depth = Layer::MIDDLE;
    _sprite->rotation = _rotationDefault;
    _sprite->anchorX = Width() / 2;
    _sprite->anchorY = Height() / 2;
    _sprite->color = Color();
    _sprite->position = _position;
}


void Sprite::Draw()
{
    // adiciona o sprite na lista de desenho
    if(this != nullptr)
    Engine::renderer->Draw(_sprite);
}

// ---------------------------------------------------------------------------------

void Sprite::SetImage(Image* img)
{
    if (img->Filename() != _image->Filename()) {
        _image = img;
        _sprite->texture = _image->View();
        _sprite->width = _image->Width();
        _sprite->height = _image->Height();
    }
}

// ---------------------------------------------------------------------------------

void Sprite::SetImage(const std::string _filename)
{
    if (_filename != _image->Filename()) {
        _image = new Image(_filename);
        _sprite->texture = _image->View();
        _sprite->width = _image->Width();
        _sprite->height = _image->Height();
    }
}

// ---------------------------------------------------------------------------------

Rect*  Sprite::GetRect() const 
{ 
    float w = HalfWidth();
    float h = HalfHeight();
    float Ax = _position.x() - w;
    float Ay = _position.y() - h;
    float Bx = _position.x() + w;
    float By = _position.y() + h;
    return new Rect(Position(Ax, Ay), Position(Bx, By));
}

Circle*  Sprite::GetCircle() const 
{
    float r = (HalfHeight() + HalfWidth()) / 2;
    return new Circle(r);
}

// ---------------------------------------------------------------------------------

void Sprite::MoveTo(const Position& position) {
    this->_sprite->position.MoveTo(position);
}
void Sprite::MoveTo(Position* position) {
    this->_sprite->position.MoveTo(position);

}
void Sprite::TranslateTo(const Vector& delta) {
    this->_sprite->position.TranslateTo(delta);
}