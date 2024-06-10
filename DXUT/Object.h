#ifndef DXUT_IOBJECT_H
#define DXUT_IOBJECT_H

// -----------------------------------------------------------------------------
#include "Window.h"                 // janela usada para o jogo
#include "Input.h"                 // janela usada para o jogo
#include "Position.h"
#include "Sprite.h"
#include "Vector.h"
#include "Geometry.h"
#include "Movable.h"

// -----------------------------------------------------------------------------

class Object : public Movable{
private :
protected:
    static Window*& window;        // janela do jogo
    static Input*& input;        // janela do jogo 
    static float& gameTime;      // tempo do último quadro

    // -----------------------------------------------------------------------------
    uint type;                                          // tipo do objeto
    Sprite  *_sprite    = nullptr;
    Geometry* _bbox;                                 // bounding box do objeto

public:
    Object();                       // construtor padrão
    //virtual ~Object() = 0;                      // destrutor virtual


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

    // -----------------------------------------------------------------------------
    void SetSprite(Sprite* sprite);
    void SetScale(float scale);


    // retorna tipo do objeto
    virtual uint Type() const;
    // muda a bounding box do objeto
    virtual void BBox(Geometry* bb);

    // retorna a bounding box do objeto
    virtual Geometry* BBox() const;
    virtual float Left() const;
    virtual float Right() const;
    virtual float Top() const;
    virtual float Down() const;
    virtual float Width() const;
    virtual float Height() const;


    virtual void MoveTo(const Position& position) override;
    virtual void MoveTo(Position* position) override;
    virtual void TranslateTo(const Vector& delta) override;

};


// -----------------------------------------------------------------------------
// Métodos Inline
// retorna tipo do objeto
inline uint Object::Type() const { return type;}
// retorna a bounding box do objeto
inline Geometry* Object::BBox() const{ return _bbox;}

inline  float Object::Left() const { return _sprite ? position().x() - _sprite->HalfWidth() : position().x(); }
inline  float Object::Right() const { return _sprite ? position().x() + _sprite->HalfWidth() : position().x(); }
inline  float Object::Top() const { return _sprite ? position().y() - _sprite->HalfHeight() : position().y(); }
inline  float Object::Down() const { return _sprite ? position().y() + _sprite->HalfHeight() : position().y(); }
inline  float Object::Width() const { return _sprite->Width(); }
inline  float Object::Height() const { return _sprite->Height(); }
inline void Object::SetScale(float scale) { _sprite->SetScale(scale); }

// -----------------------------------------------------------------------------

#endif


