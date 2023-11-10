#ifndef _MCS_H
#define _MCS_H

#include "Hasheable.h"
//Solution (0,0,0)
class MCS : public Hasheable{
private:
    int missionaries = 0;
    int cannibals = 0;
    int boatOnLeft = 1;
    int missionariesOtherSide = 0;
    int cannibalsOtherSide = 0;
public:
    MCS() = default;
    MCS(int _m, int _c, int boat = 1);
    bool Valid() const;
    //(m,c,b)
    float Compare(const MCS& other) const;
    void Move(int miss, int can);
    bool Equal(const MCS& other) const;

    std::size_t customHash() const override;
    bool operator==(const Hasheable& other) const override;
};

#endif