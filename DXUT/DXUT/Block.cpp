#include "Block.h"
#include "Breakout.h"
#include "Ball.h"

Block::Block(Image* img) {
    _position = new Position();
    this->SetSprite(new Sprite(img));
    _speedMagnitude = 150;
    this->SetSpeed(Vector::Zero);
    _sprite->SetLayer(Layer::LOWER);
    // tipo do objeto
    type = BLOCK;
    BBox(_sprite->GetRect());
}


void Block::Update() {
    if (destroyed) {
        Translate((_speed + Vector::Down * _speedMagnitude) * gameTime);
    }
    if (Top() > window->Height())
        Breakout::scene->Delete();
}

void Block::OnCollision(Object* obj) {
    if (obj->Type() == BALL) {
        Ball* ball = (Ball*)obj;
        const Vector v(obj->Speed().X(), 0);
        SetSpeed(v);
        destroyed = true;
    }
}