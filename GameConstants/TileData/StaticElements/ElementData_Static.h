#pragma once

#include "../ElementData.h"

class ElementData_Static : public ElementData
{
    public:
        ElementData_Static(const std::string& name, int textureID, float size_x, float size_y, float posOffset_x, float posOffset_y);

    private:

};