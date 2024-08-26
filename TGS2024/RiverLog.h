#pragma once
#include "ObjectBase.h"
class RiverLog :
    public ObjectBase
{
private:
    int riverlog_img;//丸太画像入れる用

public:
    RiverLog();
    ~RiverLog();

    void Update();
    void Draw()const;
};

