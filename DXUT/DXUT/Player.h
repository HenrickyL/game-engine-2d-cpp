#ifndef IA_TEST_PLAYER_H
#define IA_TEST_PLAYER_H

#include "Object.h"
#include <vector>
#include "MovimentAction.h"
#include "Node.h"
#include "Dictionary.h"
#include "Timer.h"
using std::vector;

class Player : public Object {
private:
    Position initial;
    Position target;
    Node<Position>* path = nullptr;
    vector<Action<Position>*> actions;
    Node<Position>* pivot = nullptr;
    Dictionary<Position>* dictionary;
    Timer* interTimer;
    int pathLength = 0;
    bool run = false;
    float animationTime = 3;

    void Search();
public:
    Player(Image* img, const Position& p);
    ~Player();
    void OnCollision(Object* obj);
    void Update();
    void SetTarget(const Position& p);
};

#endif