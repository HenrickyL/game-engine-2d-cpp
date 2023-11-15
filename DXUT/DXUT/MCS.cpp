#include "MCS.h"


MCS::MCS(int countMissionaries, int countCannibals, int boat, int _m, int _c) 
    : missionaries(countMissionaries), cannibals(countCannibals), boatOnLeft(boat), missionariesOtherSide(_m), cannibalsOtherSide(_c) 
{}

bool MCS::IsValid() const {
    if (this->cannibalsOtherSide < 0 || this->missionariesOtherSide < 0) return false;
    // Verificar se há mais missionários do que canibais do lado de origem
    int missionariosLeft = missionaries - missionariesOtherSide;
    int canibaisLeft = cannibals - cannibalsOtherSide;
    bool leftValid = missionariosLeft > 0 ? missionariosLeft >= canibaisLeft : true;

    // Verificar se há mais missionários do que canibais do lado oposto
    bool RightValid = missionariesOtherSide > 0? missionariesOtherSide >= cannibalsOtherSide : true;

    // Verificar se o barco não está levando mais canibais do que missionários
    /*int canibaisOnBoat = (boatOnLeft == 1) ? cannibalsOtherSide : (cannibals - cannibalsOtherSide);
    int missionariosOnBoat = (boatOnLeft == 1) ? missionariesOtherSide : (missionaries - missionariesOtherSide);
    bool boatDoesNotTakeMoreCannibals = canibaisOnBoat <= missionariosOnBoat;*/

    // Verificar se todas as condições são atendidas
    return leftValid && RightValid /* && boatDoesNotTakeMoreCannibals*/;
}
//(m,c,b)
float MCS::Compare(const MCS& target) const {
    // Calcular a diferença entre o estado atual e o estado objetivo
    int differenceMissionaries = target.missionariesOtherSide - missionariesOtherSide;
    int differenceCannibals = target.cannibalsOtherSide - cannibalsOtherSide;
    int differenceBoat = target.boatOnLeft - boatOnLeft;

    // Elevar as diferenças ao quadrado para penalizar mais fortemente diferenças maiores
    float squaredMissionaries = differenceMissionaries * differenceMissionaries;
    float squaredCannibals = differenceCannibals * differenceCannibals;
    float squaredBoat = differenceBoat * differenceBoat;

    // Calcular uma heurística baseada nessas diferenças ao quadrado
    float heuristic = squaredMissionaries + squaredCannibals + squaredBoat;

    return heuristic;
}

void MCS::Move(int miss, int can) {
    if (boatOnLeft > 0) {
        missionariesOtherSide += miss;
        cannibalsOtherSide += can;
    }
    else {
        missionariesOtherSide -= miss;
        cannibalsOtherSide -= can;
    }
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

std::string MCS::ToString() const {
    std::string str = "(";
    str += std::to_string(missionariesOtherSide) +", ";
    str += std::to_string(cannibalsOtherSide) + ", ";
    str += std::to_string(boatOnLeft);
    str += ")";
    return str.c_str();
}