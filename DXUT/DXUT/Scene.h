#ifndef DXUT_SCENE_H
#define DXUT_SCENE_H

// ---------------------------------------------------------------------------------
// Inclusões

#include <list>                         // lista da biblioteca SLT 
using std::list;                        // acessa list sem precisar do std::
class Object;                           // declaração avançada

// ---------------------------------------------------------------------------------

class Scene
{
private:
    list <Object*> objects;             // lista de objetos 
    list <Object*>::iterator next;      // iterador para próximo elemento da lista
    list <Object*>::iterator it;        // iterador para elemento atual

public:
    Scene();                            // construtor
    ~Scene();                           // destrutor da cena

    void Add(Object* obj);             // adiciona um objeto a lista
    void Update();                      // atualiza todos os objetos da cena
    void Draw();                        // desenha todos os objetos da cena

    void Begin();                       // inicia percurso na lista de objetos
    Object* Next();                    // retorna próximo objeto da lista
    void Remove();                      // remove último objeto retornado por Next()
};

// ---------------------------------------------------------------------------------

#endif