﻿#ifndef DXUT_IOBJECT_H
#define DXUT_IOBJECT_H

// -----------------------------------------------------------------------------
#include "Window.h"                 // janela usada para o jogo
#include "Input.h"                 // janela usada para o jogo
#include "Position.h"
#include "Sprite.h"
#include "Vector.h"
#include "Geometry.h"

// -----------------------------------------------------------------------------

class Object
{
private :
protected:
    static Window*& window;        // janela do jogo
    static Input*& input;        // janela do jogo 
    static float& gameTime;      // tempo do último quadro

    // -----------------------------------------------------------------------------
    Position* _position = nullptr;                   // coordenadas do objeto
    uint type;                                          // tipo do objeto
    Sprite  *_sprite    = nullptr;
    Vector   _speed      = Vector::Right;
    Geometry* _bbox;                                 // bounding box do objeto

public:
    Object();                       // construtor padrão
    ~Object();                      // destrutor virtual

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

    // atualiza estado do objeto - pura
    virtual void Update() = 0;

    // desenha o objeto na tela
    virtual void Draw();

    // faz a resolução de colisão do objeto
    virtual void OnCollision(Object* obj);

    // -----------------------------------------------------------------------------

    Vector Speed() const;
    Position GetPosition() const;

    // -----------------------------------------------------------------------------

    void SetSpeed(const Vector speed);
    void SetSprite(Sprite* sprite);

    // retorna tipo do objeto
    virtual uint Type() const;
    // muda a bounding box do objeto
    virtual void BBox(Geometry* bb);

    // retorna a bounding box do objeto
    virtual Geometry* BBox() const;

};


// -----------------------------------------------------------------------------
// Métodos Inline

inline Vector Object::Speed() const { return _speed;}
inline void Object::SetSpeed(const Vector speed){ _speed = speed;}
inline Position Object::GetPosition() const { return *_position; }

// retorna tipo do objeto
inline uint Object::Type() const { return type;}
// retorna a bounding box do objeto
inline Geometry* Object::BBox() const{ return _bbox;}
// -----------------------------------------------------------------------------

#endif


