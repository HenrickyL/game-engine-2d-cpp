#ifndef _BREAKOUT_BALL_H_
#define _BREAKOUT_BALL_H_
// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"
#include "Player.h"
// ---------------------------------------------------------------------------------
class Ball : public Object {
private:
	Player* player = nullptr;
	float _speedMagnitude = 300;
public:
	Ball(Player* p, Image* img);                   // construtor
	~Ball();                            // destrutor

	void OnCollision(Object* obj);     // tratamento de colisão
	void Update();                      // atualização do objeto
};

#endif