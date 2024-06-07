#ifndef UT_Ground_H
#define UT_Ground_H

//namespace P_UI {

#include "Movable.h" 
#include "Colored.h" 
#include "IDrawable.h"

    class GroundUI : public Movable, public Colored, public virtual IDrawable {
    protected:
        int _length;
        int _increment = 1.0f;
    public:
        GroundUI();
        GroundUI(int length, const Color color = Color::WHITE);
        GroundUI(const Position& pos, int length, const Color color = Color::WHITE);

        int length()const;
        void SetLength(int value);
    };
//}
#endif