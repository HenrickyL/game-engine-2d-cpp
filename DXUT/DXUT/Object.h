#ifndef DXUT_IOBJECT_H
#define DXUT_IOBJECT_H

// -----------------------------------------------------------------------------
#include "Window.h"                 // janela usada para o jogo
#include "Input.h"                 // janela usada para o jogo

// -----------------------------------------------------------------------------

class Object
{
protected:
    static Window*& window;        // janela do jogo
    static Input*& input;        // janela do jogo 
    static float& gameTime;      // tempo do último quadro

	float x, y, z;                  // coordenadas do objeto 
    float _speed = 1.0f;

public:
    Object();                       // construtor padrão
    virtual ~Object();              // destrutor virtual

    // ------------------------
    // funções virtuais    
    // ------------------------
    // podem ser sobrescritas na classe derivada
    // e chamadas corretamente mesmo usando um
    // ponteiro para a classe base

    // move o objeto por (deltaX, deltaY, deltaZ)
    virtual void Translate(float dx, float dy, float dz = 0.0f);

    // move o objeto para as coordenadas (x,y,z) indicadas
    virtual void MoveTo(float px, float py, float pz);

    // move o objeto para as coordenadas (x,y) indicadas
    virtual void MoveTo(float px, float py);

    // ------------------------
    // funções virtuais puras    
    // ------------------------     
    // devem ser obrigatoriamente sobrescritas na classe derivada

    // atualiza estado do objeto
    virtual void Update() = 0;

    // desenha o objeto na tela
    virtual void Draw() = 0;

    float Speed() const;
    void SetSpeed(const float speed);

    float X();
    float Y();

};


// -----------------------------------------------------------------------------
// Métodos Inline

inline float Object::Speed() const
{    return _speed;}
inline void Object::SetSpeed(const float speed)
{    _speed = speed;}

inline float Object::X()
{
    return x;
}
inline float Object::Y()
{
    return y;
}
// -----------------------------------------------------------------------------

// move o objeto por (deltaX, deltaY, deltaZ)
inline void Object::Translate(float dx, float dy, float dz)
{
    x += dx; y += dy; z += dz;
}

// move o objeto para as coordenadas (x,y,z) indicadas
inline void Object::MoveTo(float px, float py, float pz)
{
    x = px; y = py; z = pz;
}

// move o objeto para as coordenadas (x,y) indicadas
inline void Object::MoveTo(float px, float py)
{
    x = px; y = py;
}

// -----------------------------------------------------------------------------

#endif


