#ifndef UT_ORIGIN_GIZMO_UI_H
#define UT_ORIGIN_GIZMO_UI_H

//namespace P_UI {

#include "Movable.h" 
#include "Color.h" 
#include "IDrawable.h"

class OriginGizmoUI : public Movable, public virtual IDrawable {
protected:
    float _length = 1.0f;
    float _stroke = 2.5f;
    Color _axisX = Color::RED;
    Color _axisY = Color::GREEN;
    Color _axisZ = Color::BLUE;

public:
    OriginGizmoUI();
    OriginGizmoUI(float length);
    OriginGizmoUI(const Position& pos, float length = 2.0f);

    float length()const;
    void SetLength(int value);
};
//}
#endif