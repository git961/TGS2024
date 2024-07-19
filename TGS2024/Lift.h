#pragma once
#include "LiftBase.h"
class Lift :
    public LiftBase
{
private:
    int lift_img;
public:
    Lift(float set_x, float set_y);
    ~Lift();

    void Update();
    void Draw() const;
};

