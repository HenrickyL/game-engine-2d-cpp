#ifndef _MCS_H
#define _MCS_H
#include <string>
#include "Hasheable.h"
//Solution (m,c,b)
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

    int MissionariesTarget()const;
    int CannibalsTarget() const;

    int MissionariesOrigin()const;
    int CannibalsOrigin() const;

    int Boat() const;


};

inline int MCS::MissionariesTarget()const { return missionariesOtherSide; }
inline int MCS::CannibalsTarget() const { return cannibalsOtherSide; }
inline int MCS::MissionariesOrigin()const { return missionaries - missionariesOtherSide; }
inline int MCS::CannibalsOrigin() const { return cannibals - cannibalsOtherSide; }
inline int MCS::Boat() const { return boatOnLeft; }


#endif