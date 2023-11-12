#ifndef DXUT_SCENE_H
#define DXUT_SCENE_H

// ---------------------------------------------------------------------------------
// Inclusões
#include "Geometry.h"                           // bounding box dos objetos
#include <list>                         // lista da biblioteca SLT 
using std::list;                        // acessa list sem precisar do std::
using std::pair;                                // pair sem precisar do std::
class Object;                           // declaração avançada

// ---------------------------------------------------------------------------------
enum ObjectGroup
{
    STATIC,                                     // não colidem entre si
    MOVING                                      // colidem entre si e com estáticos
};

using ObjectPair = pair<Object*, Object*>;      // par de objetos em colisão
using ObjectDel = pair<Object*, int>;          // <objeto,tipo> a deletar da cena

// ---------------------------------------------------------------------------------

/// TODO: add lista de desenho, e possibilidade de remover dela. assim podemos remover de uma lista específica como apenas de colisão.
/// TODO: add Clear para limpar a cena, ou Object::Reset e um Scene::Reset


class Scene
{
private:
    list<Object*> statics;                      // lista de objetos estáticos
    list<Object*> moving;                       // lista de objetos em movimento

    list<ObjectPair> collisions;                // lista de pares de objetos em colisão
    list<ObjectDel> toDelete;                   // lista de objetos a deletar da cena

    list<Object*>::iterator its;                // iterador para elemento estático
    list<Object*>::iterator itm;                // iterador para elemento em movimento
    list<Object*>::iterator it;                 // iterador para elemento atual
    int processing = STATIC;                    // indica qual lista de objetos está sendo processada

    bool Collision(Point* p, Point* q);       // colisão entre ponto e ponto
    bool Collision(Point* p, Rect* r);        // colisão entre ponto e retângulo    
    bool Collision(Point* p, Circle* c);      // colisão entre ponto e círculo

    bool Collision(Rect* ra, Rect* rb);       // colisão entre retângulos
    bool Collision(Rect* r, Point* p);        // colisão entre retângulo e ponto (inline)
    bool Collision(Rect* r, Circle* c);       // colisão entre retângulo e círculo

    bool Collision(Circle* ca, Circle* cb);   // colisão entre círculos
    bool Collision(Circle* c, Point* p);      // colisão entre círculo e ponto (inline)
    bool Collision(Circle* c, Rect* r);       // colisão entre círculo e retângulo (inline)

    bool Collision(Mixed* m, Geometry* s);    // colisão entre geometria mista e uma forma qualquer
    bool Collision(Geometry* s, Mixed* m);    // colisão entre geometria mista e uma forma qualquer (inline)

    void ProcessDeleted();                      // apaga elementos marcados para exclusão

public:
    Scene();                                    // construtor
    ~Scene();                                   // destrutor da cena

    void Add(Object* obj, ObjectGroup type);           // adiciona objeto na lista STATIC ou MOVING da cena
    void Remove(Object* obj, ObjectGroup type);         // remove objeto da cena sem deletar
    void Remove();                              // remove objeto sendo processado na cena sem deletar
    void Delete(Object* obj, ObjectGroup type);        // deleta objeto da lista indicada (STATIC ou MOVING)
    void Delete();                              // deleta o objeto cujo Update/Draw está sendo executado

    uint Size();                                // retorna a quantidade de objetos na cena

    void Begin();                               // inicia percurso na lista de objetos
    Object* Next();                            // retorna próximo objeto da lista

    void Update();                              // atualiza todos os objetos da cena
    void Draw();                                // desenha todos os objetos da cena
    void DrawBBox();                            // desenha a bounding box dos objetos na cena

    bool Collision(Object* oa, Object* ob);   // verifica se há colisão entre dois objetos
    void CollisionDetection();                  // trata a colisão entre objetos da cena
    bool Empty() const;
};
// --------------------------------------------------------------------------------
// Funções Membro Inline

// colisão entre retângulo e ponto
inline bool Scene::Collision(Rect* r, Point* p)
{ return Collision(p, r);}

// colisão entre círculo e ponto
inline bool Scene::Collision(Circle* c, Point* p)
{ return Collision(p, c);}

// colisão entre círculo e retângulo
inline bool Scene::Collision(Circle* c, Rect* r)
{ return Collision(r, c);}

// colisão entre geometria mista e uma forma qualquer
inline bool Scene::Collision(Geometry* s, Mixed* m)
{ return Collision(m, s);}

// ---------------------------------------------------------------------------------

#endif