#include "Alien.h"

// ---------------------------------------------------------------------------------

Alien::Alien(Image* img)
{
    _position = new Point();
    this->SetSprite(new Sprite(img));
    this->SetSpeed(Vector::Right * _speedScalar);
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
    this->Translate(_speed * gameTime);

    // alien saindo pela esquerda
    if (_speed <=> Vector::Left &&_position->X() + _sprite->HalfWidth() < 0)
        this->MoveTo(Point(window->Width(), _position->Y()));

    // alien saindo pela direita
    if (_speed <=> Vector::Right && _position->X() > window->Width() + _sprite->HalfWidth())
        this->MoveTo(Point(-_sprite->Width(), _position->Y()));
}

// ---------------------------------------------------------------------------------

void Alien::SetDirection(const Vector& direction)
{
    this->SetDirection(direction * _speedScalar);
}
