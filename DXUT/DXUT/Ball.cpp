#include "Ball.h"
// ---------------------------------------------------------------------------------
#include "Breakout.h"
// ---------------------------------------------------------------------------------
Ball::Ball(Player* p, Image* img) {
    _position = new Position();
    this->SetSprite(new Sprite(img));
    this->SetSpeed((Vector::Up + Vector::Right)*300);
    _sprite->SetLayer(Layer::MIDDLE);

    // tamanho do player é 100x20
    BBox(_sprite->GetCircle());

    // centraliza o jogador
    MoveTo(Position(
        p->GetPosition().X(),
        p->Top()-_sprite->HalfHeight()));
    
    // tipo do objeto
    type = BALL;
}
// ---------------------------------------------------------------------------------

Ball::~Ball() {
    delete _position;
    delete _sprite;
    delete _bbox;
}

// ---------------------------------------------------------------------------------

void Ball::OnCollision(Object* obj) {
    if (obj->Type() == PLAYER) {
        _speed.SetX(_speed.X() + obj->Speed().Unit().X());
        _speed.SetY(-_speed.Y());
    }
}
// ---------------------------------------------------------------------------------
void Ball::Update() {
    this->Translate(_speed * gameTime);
    
    if (this->Top() <= 0 || this->Down() >= window->Height()) {
        _speed.SetY(-_speed.Y());
    }

    if (this->Right() >= window->Width() || this->Left() <= 0) {
        _speed.SetX(-_speed.X());
    }
}

// ---------------------------------------------------------------------------------
