#include "MCS.h"


MCS::MCS(int _m, int _c, int boat) : missionaries(_m), cannibals(_c), boatOnLeft(boat) {}

bool MCS::Valid() const {
    //origin side
    bool origin = (missionaries - missionariesOtherSide) < (cannibals - cannibalsOtherSide);
    bool otherSide = missionariesOtherSide - cannibalsOtherSide;
    return origin || otherSide;
}
//(m,c,b)
float MCS::Compare(const MCS& other) const {
    return (other.cannibalsOtherSide - cannibalsOtherSide) +
        (other.missionariesOtherSide - missionariesOtherSide) + boatOnLeft;
}

void MCS::Move(int miss, int can) {
    missionariesOtherSide += miss;
    cannibalsOtherSide += can;
    boatOnLeft = boatOnLeft == 0 ? 1 : 0;
}


std::size_t MCS::customHash() const {
    // Use std::hash para calcular os hashes dos atributos relevantes
    std::size_t missionariesHash = std::hash<int>{}(missionaries);
    std::size_t cannibalsHash = std::hash<int>{}(cannibals);
    std::size_t boatHash = std::hash<int>{}(boatOnLeft);
    std::size_t missionariesOtherSideHash = std::hash<int>{}(missionariesOtherSide);
    std::size_t cannibalsOtherSideHash = std::hash<int>{}(cannibalsOtherSide);

    // Combine os hashes usando XOR ou outra operação desejada
    return missionariesHash ^ cannibalsHash ^ boatHash ^ missionariesOtherSideHash ^ cannibalsOtherSideHash;
}

bool MCS::operator==(const Hasheable& other) const {
    if (const MCS* mcs = dynamic_cast<const MCS*>(&other)) {
        return missionaries == mcs->missionaries &&
            cannibals == mcs->cannibals &&
            boatOnLeft == mcs->boatOnLeft &&
            missionariesOtherSide == mcs->missionariesOtherSide &&
            cannibalsOtherSide == mcs->cannibalsOtherSide;
    }
    return false;
}

bool MCS::operator==(const MCS& other) const {
    if (const MCS* mcs = dynamic_cast<const MCS*>(&other)) {
        return missionaries == mcs->missionaries &&
            cannibals == mcs->cannibals &&
            boatOnLeft == mcs->boatOnLeft &&
            missionariesOtherSide == mcs->missionariesOtherSide &&
            cannibalsOtherSide == mcs->cannibalsOtherSide;
    }
    return false;
}

bool MCS::Equal(const MCS& other) const {
    return missionaries == other.missionaries &&
        cannibals == other.cannibals &&
        boatOnLeft == other.boatOnLeft &&
        missionariesOtherSide == other.missionariesOtherSide &&
        cannibalsOtherSide == other.cannibalsOtherSide;
}