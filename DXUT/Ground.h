#ifndef UT_Ground_H
#define UT_Ground_H

//namespace P_UI {

#include "Movable.h" 
#include "Colored.h" 

    class Ground : public Movable, public Colored {
    protected:
        int _length;
        int _increment = 1.0f;
    public:
        Ground();
        Ground(int length, const Color color = Color::WHITE);
        Ground(const Position& pos, int length, const Color color = Color::WHITE);

        int length()const;
        void SetLength(int value);

        virtual void Draw() const = 0;
    };
//}
#endif