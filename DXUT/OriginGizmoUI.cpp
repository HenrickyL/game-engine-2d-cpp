#include "OriginGizmoUI.h"

OriginGizmoUI::OriginGizmoUI() {}
OriginGizmoUI::OriginGizmoUI(float length) {}
OriginGizmoUI::OriginGizmoUI(const Position& pos, float length) : Movable(pos), _length(length) {}

float OriginGizmoUI::length()const { return _length; }
void OriginGizmoUI::SetLength(int value) { _length = value; }