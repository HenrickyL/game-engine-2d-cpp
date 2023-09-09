#include "Breakout.h"
#include "Player.h"
#include "Ball.h"

// ---------------------------------------------------------------------------------

Player::Player(Image* img)
{
    _position = new Position();
    this->SetSprite(new Sprite(img));
    this->SetSpeed(Vector(Vector::Right * 500));
    _sprite->SetLayer(Layer::MIDDLE);

    // tamanho do player é 100x20
    BBox(_sprite->GetRect());

    // centraliza o jogador
    const Position loc(window->Center().X(), window->Height() - 30.0f);
    MoveTo(loc);
    // estado inicial do jogo
    state = STOPED;
    // tipo do objeto
    type = PLAYER;

}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete _position;
    delete _sprite;
    delete _bbox;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    //// bola colidiu com o player
    //if (obj->Type() == BALL)
    //{
    //    Ball* ball = (Ball*)obj;
    //    ball->velY = -ball->velY;
    //}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // inicia o jogo com barra de espaço
    if (state == STOPED && input->KeyDown(VK_SPACE))
        state = PLAYING;

    // desloca jogador horizontalmente
    if (input->KeyDown(VK_RIGHT) && this->Right() <= window->Width()) {
        if(_speed <=> Vector::Left)
            _speed = _speed * -1;
        Translate(_speed * gameTime);
    }
    if (input->KeyDown(VK_LEFT) && this->Left() >= 0) {
        if (_speed <=> Vector::Right)
            _speed = _speed * -1;
        Translate(_speed * gameTime);
    }
}