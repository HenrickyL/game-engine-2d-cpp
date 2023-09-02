#ifndef _FROGGER_FROGGER_H_
#define _FROGGER_FROGGER_H_
// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"

class Frogger: public Object
{
private:
	Sprite* _sprite;

    float _jumpDistance = 40.0f;

    float initX, initY;


    void InputCharacter();
public:
    Frogger();
    ~Frogger();

    void Update();
    void Draw();

    int Width() const;
    int Height() const;
    bool IsValidPosition(float newX, float newY);
    void Reset();

};
// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Frogger::Draw()
{    _sprite->Draw(x, y, z);}

inline int Frogger::Width() const
{    return _sprite->Width();}

inline int Frogger::Height() const
{    return _sprite->Height();}
#endif