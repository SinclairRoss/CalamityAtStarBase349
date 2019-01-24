#pragma once

#include "../ElementData.h"

class ElementData_Wall : public ElementData
{
    public:
        ElementData_Wall(const std::string& name, int textureID, float size_x, float size_y);

    private:
};