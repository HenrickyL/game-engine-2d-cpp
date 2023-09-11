#ifndef _BREAKOUT_BLOCK_H_
#define _BREAKOUT_BLOCK_H_
// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"
#include "Player.h"
// ---------------------------------------------------------------------------------
class Block : public Object {
private:
	bool destroyed = false;
public:
	Block(Image* img);                   // construtor

	void OnCollision(Object* obj);     // tratamento de colis�o
	void Update();                      // atualiza��o do objeto
};
#endif