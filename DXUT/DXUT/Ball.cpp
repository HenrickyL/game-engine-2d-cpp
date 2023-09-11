#include "Ball.h"
// ---------------------------------------------------------------------------------
#include "Breakout.h"
// ---------------------------------------------------------------------------------
Ball::Ball(Player* p, Image* img) {
    _position = new Position();
    this->SetSprite(new Sprite(img));
    this->SetSpeed((Vector::Up + Vector::Right) * 300);
    _sprite->SetLayer(Layer::MIDDLE);

    // tamanho do player � 100x20

    // centraliza o jogador
    player = p;
    MoveTo(Position(
        p->GetPosition().X(),
        p->Top() - _sprite->HalfHeight() - 5));
    // tipo do objeto
    type = BALL;
    BBox(_sprite->GetCircle());

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
    if (player->state == PLAYING)
        this->Translate(_speed * gameTime);
    else {
        MoveTo(Position(
            player->GetPosition().X(),
            player->Top() - _sprite->HalfHeight()-5));
    }

    if (this->Top() < 0 ) {
        _speed.SetY(-_speed.Y());
    }

    if (this->Right() > window->Width() || this->Left() < 0) {
        _speed.SetX(-_speed.X());
    }

    if (this->Down() > window->Height()) {
        Breakout::Instance()->Reset();
    }
}