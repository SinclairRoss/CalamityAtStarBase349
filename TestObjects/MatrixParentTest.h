#pragma once

#include "Core\Renderables\Sprite.h"

class MatrixParentTest
{
    public:
        MatrixParentTest();

        void Update();

    private:
        Sprite m_Core;
        Sprite m_Satellite_1;
        Sprite m_Satellite_2;
};
