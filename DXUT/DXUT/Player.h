#ifndef IA_TEST_PLAYER_H
#define IA_TEST_PLAYER_H

#include "Object.h"
#include <vector>
using std::vector;


class Player : public Object {
private:
public:
    Player(Image* img);
    void OnCollision(Object* obj);
    void Update();
};

#endif