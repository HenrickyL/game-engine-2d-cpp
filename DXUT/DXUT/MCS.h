#ifndef _MCS_H
#define _MCS_H
#include <string>
#include "Hasheable.h"
//Solution (0,0,0)
class MCS : public Hasheable{
private:
    int missionariesOtherSide = 0;
    int cannibalsOtherSide = 0;
    int boatOnLeft = 1;
    int missionaries = 0;
    int cannibals = 0;
public:
    MCS() = default;
    MCS(int countMissionaries, int countCannibals, int boat = 1, int _m = 0, int _c = 0);
    bool IsValid() const;
    //(m,c,b)
    float Compare(const MCS& other) const;
    void Move(int miss, int can);
    bool Equal(const MCS& other) const;
    std::string ToString() const;

    std::size_t customHash() const override;
    bool operator==(const Hasheable& other) const override;
    bool operator==(const MCS& other) const;

};

#endif