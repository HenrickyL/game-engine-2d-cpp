#include "Ground.h"

Ground::Ground(){}
Ground::Ground(int length, const Color color) : Colored(color), _length(length){}
Ground::Ground(const Position& pos, int length, const Color color) : Movable(pos), Colored(color), _length(length) {}

int Ground::length()const {return _length;}
void Ground::SetLength(int value) { _length = value; }