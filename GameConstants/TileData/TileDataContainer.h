#pragma once

#include <vector>

#include "StaticElements\ElementData_Static.h"
#include "Interactables\ElementData_Interactable.h"
#include "Floor\ElementData_Floor.h"
#include "Wall\ElementData_Wall.h"

#include "Core\Utils\Utils.h"

class TileDataContainer
{
    public:
        TileDataContainer();

        template <typename T>
        int GetElementIDWithName(const std::string& name) const
        {
            static_assert(std::is_base_of<ElementData, T>::value, "T must inherit from ElementData");

            int index = Utils::IndexOf_If<T>(GetElementList<T>(), [&](const T& data) { return data.GetName() == name; });
            return index;
        }

        template <typename T>
        const T* GetElementDataWithID(int id) const
        {
            static_assert(std::is_base_of<ElementData, T>::value, "T must inherit from ElementData");

            const T* data = &GetElementList<T>().at(id);
            return data;
        }

        template <typename T>
        int GetElementCount() const
        {
            static_assert(std::is_base_of<ElementData, T>::value, "T must inherit from ElementData");

            int size = GetElementList<T>().size();
            return size;
        }

    private:

        template <typename T>
        const std::vector<T>& GetElementList() const
        {}

        template <>
        const std::vector<ElementData_Floor>& GetElementList<ElementData_Floor>() const
        { return m_ElementData_Floor; }

        template <>
        const std::vector<ElementData_Wall>& GetElementList<ElementData_Wall>()const
        { return m_ElementData_Wall; }

        template <>
        const std::vector<ElementData_Static>& GetElementList<ElementData_Static>() const 
        { return m_ElementData_Static; }

        template<>
        const std::vector<ElementData_Interactable>& GetElementList<ElementData_Interactable>() const
        { return m_ElementData_Interactable; }
         
        std::vector<ElementData_Floor> m_ElementData_Floor;
        std::vector<ElementData_Wall> m_ElementData_Wall;
        std::vector<ElementData_Static> m_ElementData_Static;
        std::vector<ElementData_Interactable> m_ElementData_Interactable;
};