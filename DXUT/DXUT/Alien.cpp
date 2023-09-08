#include "Alien.h"
#include "Galaga.h"
// ---------------------------------------------------------------------------------

Alien::Alien(Image* img)
{
    _position = new Position();
    this->SetSprite(new Sprite(img));
    this->SetSpeed(Vector::Right * _speedScalar);
    type = ALIEN;
    BBox(_sprite->GetRect());
}

// ---------------------------------------------------------------------------------

Alien::~Alien()
{
    delete _position;
    delete _sprite;
    delete _bbox;
}

// ---------------------------------------------------------------------------------

void Alien::Update()
{
    // desloca alien
    this->Translate(_speed * gameTime);

    // alien saindo pela esquerda
    if (_speed <=> Vector::Left &&_position->X() + _sprite->HalfWidth() < 0)
        this->MoveTo(Position(window->Width(), _position->Y()));

    // alien saindo pela direita
    if (_speed <=> Vector::Right && _position->X() > window->Width() + _sprite->HalfWidth())
        this->MoveTo(Position(-_sprite->Width(), _position->Y()));
}

// ---------------------------------------------------------------------------------

void Alien::SetDirection(const Vector& direction)
{
    this->SetDirection(direction * _speedScalar);
}


void Alien::OnCollision(Object* obj) {
    if (obj->Type() == MISSILE) {
        Galaga::scene->Delete(obj, MOVING);
    }
}
