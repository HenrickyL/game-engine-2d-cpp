#include "Alien.h"

// ---------------------------------------------------------------------------------

Alien::Alien(Image* img)
{
    _position = new Point();
    this->SetSprite(new Sprite(img));
    this->SetSpeed(Vector::Right * 80.0f);
}

// ---------------------------------------------------------------------------------

Alien::~Alien()
{
    delete _position;
    delete _sprite;
}

// ---------------------------------------------------------------------------------

void Alien::Update()
{
    // desloca alien
    //Vector direction = Vector::Right + _speed ;//(_speed * gameTime);
    this->Translate(_speed*gameTime);
    // mantêm os alienígenas dentro da janela
    // tamanho das imagens é 28x30

    // alien saindo pela esquerda
    if (_speed <=> Vector::Left &&_position->X() + _sprite->HalfWidth() < 0)
        this->MoveTo(Point(window->Width(), _position->Y()));

    // alien saindo pela direita
    if (_speed <=> Vector::Right && _position->X() > window->Width() + _sprite->HalfWidth())
        this->MoveTo(Point(-_sprite->Width(), _position->Y()));
}

// ---------------------------------------------------------------------------------