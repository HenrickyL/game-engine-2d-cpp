#include "GroundUI.h"

GroundUI::GroundUI(){}
GroundUI::GroundUI(int length, const Color color) : Colored(color), _length(length){}
GroundUI::GroundUI(const Position& pos, int length, const Color color) : Movable(pos), Colored(color), _length(length) {}

int GroundUI::length()const {return _length;}
void GroundUI::SetLength(int value) { _length = value; }