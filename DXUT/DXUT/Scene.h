#ifndef DXUT_SCENE_H
#define DXUT_SCENE_H

// ---------------------------------------------------------------------------------
// Inclus�es

#include <list>                         // lista da biblioteca SLT 
using std::list;                        // acessa list sem precisar do std::
class Object;                           // declara��o avan�ada

// ---------------------------------------------------------------------------------

class Scene
{
private:
    list <Object*> objects;             // lista de objetos 
    list <Object*>::iterator next;      // iterador para pr�ximo elemento da lista
    list <Object*>::iterator it;        // iterador para elemento atual

public:
    Scene();                            // construtor
    ~Scene();                           // destrutor da cena

    void Add(Object* obj);             // adiciona um objeto a lista
    void Update();                      // atualiza todos os objetos da cena
    void Draw();                        // desenha todos os objetos da cena

    void Begin();                       // inicia percurso na lista de objetos
    Object* Next();                    // retorna pr�ximo objeto da lista
    void Remove();                      // remove �ltimo objeto retornado por Next()
};

// ---------------------------------------------------------------------------------

#endif