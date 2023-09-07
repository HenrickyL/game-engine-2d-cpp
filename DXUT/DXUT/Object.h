#ifndef DXUT_IOBJECT_H
#define DXUT_IOBJECT_H

// -----------------------------------------------------------------------------
#include "Window.h"                 // janela usada para o jogo
#include "Input.h"                 // janela usada para o jogo
#include "Position.h"
#include "Sprite.h"
#include "Vector.h"

// -----------------------------------------------------------------------------

class Object
{
protected:
    static Window*& window;        // janela do jogo
    static Input*& input;        // janela do jogo 
    static float& gameTime;      // tempo do último quadro

    // -----------------------------------------------------------------------------

	Position   *_position  = nullptr;                  // coordenadas do objeto
    Sprite  *_sprite    = nullptr;
    Vector   _speed      = Vector::Right;

public:
    Object();                       // construtor padrão
    //virtual ~Object() =0;              // destrutor virtual

    // ------------------------
    // funções virtuais    
    // ------------------------
    // podem ser sobrescritas na classe derivada
    // e chamadas corretamente mesmo usando um
    // ponteiro para a classe base

    // move o objeto por (deltaX, deltaY, deltaZ)
    virtual void Translate(const Vector& delta);

    // move o objeto para as coordenadas (x,y,z) indicadas
    virtual void MoveTo(Position* position);
    virtual void MoveTo(Position position);

    // ------------------------
    // funções virtuais puras    
    // ------------------------     
    // devem ser obrigatoriamente sobrescritas na classe derivada

    // atualiza estado do objeto
    virtual void Update() = 0;

    // desenha o objeto na tela
    virtual void Draw();

    // -----------------------------------------------------------------------------

    Vector Speed() const;
    Position GetPosition() const;

    // -----------------------------------------------------------------------------

    void SetSpeed(const Vector speed);
    void SetSprite(Sprite* sprite);


};


// -----------------------------------------------------------------------------
// Métodos Inline

inline Vector Object::Speed() const { return _speed;}
inline void Object::SetSpeed(const Vector speed){ _speed = speed;}
inline Position Object::GetPosition() const { return *_position; }

// -----------------------------------------------------------------------------

#endif


