#pragma once

#include "../ElementData.h"

class ElementData_Floor: public ElementData
{
    public:
        ElementData_Floor(const std::string& name, int textureID, float size_x, float size_y, bool isTraversable);

        bool IsTraversable() const;

    private:
        bool m_IsTraversable;
};