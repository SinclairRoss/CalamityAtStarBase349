#pragma once

#include <vector>

#include "../Floor/ElementData_Floor.h"
#include "../Wall/ElementData_Wall.h"
#include "../StaticElements/ElementData_Static.h"
#include "../Interactables/ElementData_Interactable.h""

namespace TileDataReader
{
    extern std::vector<ElementData_Floor> ReadData_Floor();
    extern std::vector<ElementData_Wall> ReadData_Wall();
    extern std::vector<ElementData_Static> ReadData_Static();
    extern std::vector<ElementData_Interactable> ReadData_Interactable();

    namespace
    {
        extern InteractableType StringToInteractableType(const std::string& string);
        extern std::vector<Vector2> StringToVectorList(const std::string& string);
    }
}