#include "ElementData_Floor.h"

ElementData_Floor::ElementData_Floor(const std::string& name, int textureID, float size_x, float size_y, bool isTraversable) :
    ElementData(name, textureID, size_x, size_y, 0, 0),
    m_IsTraversable(isTraversable)
{}

bool ElementData_Floor::IsTraversable() const { return m_IsTraversable; }