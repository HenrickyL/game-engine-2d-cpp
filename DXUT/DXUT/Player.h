#ifndef IA_TEST_PLAYER_H
#define IA_TEST_PLAYER_H

#include "Object.h"
#include <vector>
#include "MovimentAction.h"
#include "Node.h"
using std::vector;


class Player : public Object {
private:
    Position initial;
    Position target;
    Node* path = nullptr;
    vector<Action*> actions;
    Node* pivot = nullptr;
    void Search();
public:
    Player(Image* img, const Position& p);
    ~Player();
    void OnCollision(Object* obj);
    void Update();
    void SetTarget(const Position& p);
};

#endif