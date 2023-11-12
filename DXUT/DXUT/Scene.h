#ifndef DXUT_SCENE_H
#define DXUT_SCENE_H

// ---------------------------------------------------------------------------------
// Inclus�es
#include "Geometry.h"                           // bounding box dos objetos
#include <list>                         // lista da biblioteca SLT 
using std::list;                        // acessa list sem precisar do std::
using std::pair;                                // pair sem precisar do std::
class Object;                           // declara��o avan�ada

// ---------------------------------------------------------------------------------
enum ObjectGroup
{
    STATIC,                                     // n�o colidem entre si
    MOVING                                      // colidem entre si e com est�ticos
};

using ObjectPair = pair<Object*, Object*>;      // par de objetos em colis�o
using ObjectDel = pair<Object*, int>;          // <objeto,tipo> a deletar da cena

// ---------------------------------------------------------------------------------

/// TODO: add lista de desenho, e possibilidade de remover dela. assim podemos remover de uma lista espec�fica como apenas de colis�o.
/// TODO: add Clear para limpar a cena, ou Object::Reset e um Scene::Reset


class Scene
{
private:
    list<Object*> statics;                      // lista de objetos est�ticos
    list<Object*> moving;                       // lista de objetos em movimento

    list<ObjectPair> collisions;                // lista de pares de objetos em colis�o
    list<ObjectDel> toDelete;                   // lista de objetos a deletar da cena

    list<Object*>::iterator its;                // iterador para elemento est�tico
    list<Object*>::iterator itm;                // iterador para elemento em movimento
    list<Object*>::iterator it;                 // iterador para elemento atual
    int processing = STATIC;                    // indica qual lista de objetos est� sendo processada

    bool Collision(Point* p, Point* q);       // colis�o entre ponto e ponto
    bool Collision(Point* p, Rect* r);        // colis�o entre ponto e ret�ngulo    
    bool Collision(Point* p, Circle* c);      // colis�o entre ponto e c�rculo

    bool Collision(Rect* ra, Rect* rb);       // colis�o entre ret�ngulos
    bool Collision(Rect* r, Point* p);        // colis�o entre ret�ngulo e ponto (inline)
    bool Collision(Rect* r, Circle* c);       // colis�o entre ret�ngulo e c�rculo

    bool Collision(Circle* ca, Circle* cb);   // colis�o entre c�rculos
    bool Collision(Circle* c, Point* p);      // colis�o entre c�rculo e ponto (inline)
    bool Collision(Circle* c, Rect* r);       // colis�o entre c�rculo e ret�ngulo (inline)

    bool Collision(Mixed* m, Geometry* s);    // colis�o entre geometria mista e uma forma qualquer
    bool Collision(Geometry* s, Mixed* m);    // colis�o entre geometria mista e uma forma qualquer (inline)

    void ProcessDeleted();                      // apaga elementos marcados para exclus�o

public:
    Scene();                                    // construtor
    ~Scene();                                   // destrutor da cena

    void Add(Object* obj, ObjectGroup type);           // adiciona objeto na lista STATIC ou MOVING da cena
    void Remove(Object* obj, ObjectGroup type);         // remove objeto da cena sem deletar
    void Remove();                              // remove objeto sendo processado na cena sem deletar
    void Delete(Object* obj, ObjectGroup type);        // deleta objeto da lista indicada (STATIC ou MOVING)
    void Delete();                              // deleta o objeto cujo Update/Draw est� sendo executado

    uint Size();                                // retorna a quantidade de objetos na cena

    void Begin();                               // inicia percurso na lista de objetos
    Object* Next();                            // retorna pr�ximo objeto da lista

    void Update();                              // atualiza todos os objetos da cena
    void Draw();                                // desenha todos os objetos da cena
    void DrawBBox();                            // desenha a bounding box dos objetos na cena

    bool Collision(Object* oa, Object* ob);   // verifica se h� colis�o entre dois objetos
    void CollisionDetection();                  // trata a colis�o entre objetos da cena
    bool Empty() const;
};
// --------------------------------------------------------------------------------
// Fun��es Membro Inline

// colis�o entre ret�ngulo e ponto
inline bool Scene::Collision(Rect* r, Point* p)
{ return Collision(p, r);}

// colis�o entre c�rculo e ponto
inline bool Scene::Collision(Circle* c, Point* p)
{ return Collision(p, c);}

// colis�o entre c�rculo e ret�ngulo
inline bool Scene::Collision(Circle* c, Rect* r)
{ return Collision(r, c);}

// colis�o entre geometria mista e uma forma qualquer
inline bool Scene::Collision(Geometry* s, Mixed* m)
{ return Collision(m, s);}

// ---------------------------------------------------------------------------------

#endif