#include "Scene.h"
#include "Object.h"    
// ---------------------------------------------------------------------------------
Scene::Scene()
{
}

// ---------------------------------------------------------------------------------

Scene::~Scene()
{
    // remove da memória os objetos da lista
    for (auto i : objects)
        delete i;
}

// ---------------------------------------------------------------------------------

void Scene::Add(Object* obj)
{
    // insere novo objeto na lista
    objects.push_back(obj);
}

// ---------------------------------------------------------------------------------

void Scene::Update()
{
    // desenha todos os objetos da lista

    next = objects.begin();
    while (next != objects.end())
    {
        // passa ao próximo objeto da lista
        // guarda iterador para o objeto atual
        it = next++;
        (*it)->Update();
    }
}

// ---------------------------------------------------------------------------------

void Scene::Draw()
{
    // desenha todos os objetos da lista

    next = objects.begin();
    while (next != objects.end())
    {
        // passa ao próximo objeto da lista
        // guarda iterador para o objeto atual
        it = next++;
        (*it)->Draw();
    }
}

// ---------------------------------------------------------------------------------

void Scene::Begin()
{
    // aponta para o primeiro elemento da lista
    next = objects.begin();
}

// ---------------------------------------------------------------------------------

Object* Scene::Next()
{
    // se apontador aponta para objeto válido
    if (next != objects.end())
    {
        // passa ao próximo objeto da lista
        // guarda iterador para o objeto atual
        it = next++;
        return *it;
    }
    else
        // chegou ao fim do conjunto
        return nullptr;
}

// ---------------------------------------------------------------------------------

void Scene::Remove()
{
    // remove um elemento que está sendo processado com Next, Update ou Draw
    delete (*it);
    objects.erase(it);
}

// ---------------------------------------------------------------------------------
